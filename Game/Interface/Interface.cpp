///@brief
#include "Interface.hpp"

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

/// 
void Interface::initialize(StateMachine * newMachine){
	
	interfaceElements.push_back(InterfaceElement( ScreenObject ("startButton", assets, sf::Vector2f(550,300), float(1)), Action ( [newMachine]{  newMachine->changeState(std::make_shared<PlayingState>());})));
	interfaceElements.push_back(InterfaceElement( ScreenObject ("editButton", assets, sf::Vector2f(150,300),float(0.35)), Action ( [newMachine]{ newMachine->changeState(std::make_shared<EditingState>());})));
	interfaceElements.push_back(InterfaceElement( ScreenObject ("settingButton", assets, sf::Vector2f(0,0), float(0.3)), Action( [newMachine] {newMachine->changeState(std::make_shared<SettingsState>());})));
	interfaceElements.push_back(InterfaceElement( ScreenObject ("closeButton", assets, sf::Vector2f(1150,350), float(0.3)), Action( []{})));
	//Pause elements
	pauseElements.push_back(InterfaceElement( ScreenObject ("settingButton", assets, sf::Vector2f(100, 200), float(0.4)), Action( [newMachine] {newMachine->changeState(std::make_shared<MenuState>());})));
	pauseElements.push_back(InterfaceElement( ScreenObject ("startButton", assets, sf::Vector2f(400, 200), float(1)), Action( [newMachine] {newMachine->changeState(newMachine->getCurrentState());})));
	machine = newMachine;
}

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
				game.restartCharacterClock();
			}
			// Back to previous state
			if(event.type == sf::Event::MouseButtonPressed && element.comparePosition(sf::Vector2f(position.x+900,position.y+440))){		
				std::cout<<"go back\n";
				pauseGame = false;
				element.changeState();
				game.restartCharacterClock();

			}
		}
	}
}


void Interface::handleInput(){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
		prevState = machine->getCurrentState();
		pauseElements[1] = InterfaceElement( ScreenObject ("startButton", assets, sf::Vector2f(400, 200), float(1)), Action( [this] {machine->changeState(prevState);}));
		machine->changeState(std::make_shared<PauseState>());
	}
}

void Interface::handleEvent(const sf::Event & event, sf::View & view){
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
		ScreenObject tmp("menuTitle", assets, sf::Vector2f(300,70), float(0.2));
		tmp.draw(window);
	}
}