///@file
#include "Interface.hpp"

/// \brief
/// Interface constructor.
/// \details
/// This is the interface constructor. 
/// @param game This has the entire Game class.
/// @Param editor This has the entire Editor class.
/// @param settings This has the entire Settings class. 
/// @param assets This has the entire Assets class. It has all the textures.
/// @param window This is where everything is drawn.
Interface::Interface(Game & game, Editor & editor, Settings & settings, AssetManager & assets, sf::RenderWindow & window):
	game(game),
	editor(editor),
	assets(assets),
	settings(settings),
	world(assets),
	window(window)
{ 
	world.loadWorld("Interface/backgroundWorld.txt");
	//world.loadWorld("World/world.txt");
 }

/// \brief
/// Initialize.
/// \details
/// This function will initialize the interfaceElements and pauseElements.
void Interface::initialize(StateMachine * newMachine){
	
	interfaceElements.push_back(InterfaceElement( [newMachine]{  newMachine->changeState(std::make_shared<PlayingState>());},"startButton", assets, sf::Vector2f(550,300), float(1) ));
	interfaceElements.push_back(InterfaceElement( [newMachine]{  newMachine->changeState(std::make_shared<EditingState>());},"editButton", assets, sf::Vector2f(150,300),float(0.35)));
	interfaceElements.push_back(InterfaceElement( [newMachine]{  newMachine->changeState(std::make_shared<SettingsState>());},"settingButton", assets, sf::Vector2f(0,0), float(0.3)));
	interfaceElements.push_back(InterfaceElement( []{},"closeButton", assets, sf::Vector2f(1150,350), float(0.3)));
	//Pause elements
	pauseElements.push_back(InterfaceElement( [newMachine]{  newMachine->changeState(std::make_shared<MenuState>());},"settingButton", assets, sf::Vector2f(100, 200), float(0.4)));
	pauseElements.push_back(InterfaceElement( [newMachine]{  newMachine->changeState(std::make_shared<PlayingState>());},"startButton", assets, sf::Vector2f(400, 200), float(1)));
	machine = newMachine;
}

/// \brief
/// Handle pause settings
/// \details
/// this will handle the pause settings.
/// It will set the position of a sprite and redirect you to the menu or resume.
void Interface::pauseSettings( const sf::Event & event, sf::View & view){
	sf::Vector2f position = view.getCenter() - (view.getSize()/2.0f);
	pauseBackground.setPosition(position.x,position.y);
	pauseBackground.setFillColor(sf::Color(0,0,0,50));
	pauseBackground.setSize(sf::Vector2f(1920,1080));


	pauseElements[0].setPosition(sf::Vector2f(position.x+600,position.y+440));
	pauseElements[1].setPosition(sf::Vector2f(position.x+900,position.y+440));
	pauseGame = true;
	//
	for(InterfaceElement& element : pauseElements){
		if(element.contains(window,view)){
			//Menu
			if(event.type == sf::Event::MouseButtonPressed && element.comparePosition(sf::Vector2f(position.x+600,position.y+440))){				

				view.setCenter(sf::Vector2f(view.getSize().x / 2, view.getSize().y / 2));
				std::cout<<"go menu\n";
				pauseGame = false;
				element.changeState();
				game.restartClocks();
			}
			// Back to previous state
			if(event.type == sf::Event::MouseButtonPressed && element.comparePosition(sf::Vector2f(position.x+900,position.y+440))){		
				std::cout<<"go back\n";
				pauseGame = false;
				element.changeState();
				game.restartClocks();

			}
		}
	}
}


/// \brief
/// Handle input.
/// \details
/// This handles the escape button, that shows the pause state and remember the previous state..
void Interface::handleInput(){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
		prevState = machine->getCurrentState();
		pauseElements[1] = InterfaceElement( [this] {machine->changeState(prevState);}, "startButton", assets, sf::Vector2f(400, 200), float(1));
		machine->changeState(std::make_shared<PauseState>());
	}
}
/// \brief
/// Handle Events.
/// \details
/// This handles all the events it gets.
void Interface::handleEvent(const sf::Event & event, sf::View & view){
	game.restartClocks();
	for( InterfaceElement & sprite : interfaceElements){
		if(sprite.contains(window, view)){
			if(event.type == sf::Event::MouseButtonPressed && sprite.comparePosition(sf::Vector2f(550, 300)) ){
				game.startWorld("World/world.txt");
				sprite.changeState();
			}
			if(event.type == sf::Event::MouseButtonPressed && sprite.comparePosition(sf::Vector2f(150, 300)) ){
				editor.selectWorld("World/world.txt");
				sprite.changeState();
			}
			if(event.type == sf::Event::MouseButtonPressed && sprite.comparePosition(sf::Vector2f(0, 0))){
				sprite.changeState();
			}
			if((event.type == sf::Event::MouseButtonPressed && sprite.comparePosition(sf::Vector2f(1150, 350)))){
				window.close();
			}
		}
	}
}


/// \brief
/// Display the game.
/// \details
/// This displays the current state of the menu or the pause state on screen .
void Interface::display(sf::View & view){
	if (pauseGame){
		view.setCenter(sf::Vector2f(view.getSize().x / 2, view.getSize().y / 2));
		for(uint_fast8_t windowLayer = 0; windowLayer <= 4; windowLayer ++){
			world.draw(window, view, windowLayer);				// Finaly, draw one more layer that's also able to draw over Characters.
		}		
		window.draw(pauseBackground);
		for( InterfaceElement & pause : pauseElements ){
			pause.draw(window);
		}
	}else{
		for(uint_fast8_t windowLayer = 0; windowLayer <= 4; windowLayer ++){
			world.draw(window, view, windowLayer);				// Finaly, draw one more layer that's also able to draw over Characters.
		}
		for( InterfaceElement & sprite : interfaceElements){
			sprite.draw(window);
		}
	}
}