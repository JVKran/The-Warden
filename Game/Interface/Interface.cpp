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

void Interface::initialize(StateMachine * machine){
	//background.setTexture(assets.getTexture("background"));
	interfaceElements.push_back(InterfaceElement( ScreenObject ("startButton", assets, sf::Vector2f(550,300), float(1)), Action ( [machine]{  machine->changeState(std::make_shared<PlayingState>());})));
	interfaceElements.push_back(InterfaceElement( ScreenObject ("editButton", assets, sf::Vector2f(150,300),float(0.35)), Action ( [machine]{ machine->changeState(std::make_shared<EditingState>());})));
	interfaceElements.push_back(InterfaceElement( ScreenObject ("settingButton", assets, sf::Vector2f(0,0), float(0.3)), Action( [machine] {machine->changeState(std::make_shared<SettingsState>());})));
	interfaceElements.push_back(InterfaceElement( ScreenObject ("settingButton", assets, sf::Vector2f(-1,-1), float(0)), Action( [machine] {machine->changeState(std::make_shared<PauseState>());})));
	//Pause elements
	pauseElements.push_back(InterfaceElement( ScreenObject ("settingButton", assets, sf::Vector2f(100, 200), float(0.4)), Action( [machine] {machine->changeState(std::make_shared<MenuState>());})));
	pauseElements.push_back(InterfaceElement( ScreenObject ("startButton", assets, sf::Vector2f(400, 200), float(1)), Action( [machine] {machine->changeState(std::make_shared<PlayingState>());})));

}

void Interface::goToPauseMenu(){ 
	interfaceElements[3].changeState();
	//view = sf::View(sf::FloatRect(0.f, 0.f, 1000.f, 580.f)); 
}

void Interface::pauseSettings( const sf::Event & event, sf::View & view){
	sf::Vector2f position = view.getCenter() - (view.getSize()/2.0f);
	pauseBackground.setPosition(position.x,position.y);
	pauseBackground.setFillColor(sf::Color(0,0,0,50));
	pauseBackground.setSize(sf::Vector2f(1000,580));

	pauseElements[0].setPosition(sf::Vector2f(position.x+200,position.y+200));
	pauseElements[1].setPosition(sf::Vector2f(position.x+500,position.y+200));
	pauseGame = true;

	for(InterfaceElement& element : pauseElements){
		if(element.contains(window,view)){
			if(event.type == sf::Event::MouseButtonPressed && element.comparePosition(sf::Vector2f(position.x+200,position.y+200))){				
				
				view = sf::View(sf::FloatRect(0.f, 0.f, 1000.f, 580.f)); 
				std::cout<<"go menu\n";
				pauseGame = false;
				element.changeState();
			}
			if(event.type == sf::Event::MouseButtonPressed && element.comparePosition(sf::Vector2f(position.x+500,position.y+200))){		
				std::cout<<"go back\n";
				pauseGame = false;
				element.changeState();

			}
		}
	}
}


void Interface::handleInput(){

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::G)){
		game.startWorld("World/world.txt");
		interfaceElements[0].changeState();
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
		 editor.selectWorld("World/world.txt");
		interfaceElements[1].changeState();
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
		interfaceElements[2].changeState();
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
		}
	}
}


void Interface::display(sf::View & view){
	if (pauseGame){
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