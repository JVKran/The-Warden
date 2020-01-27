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
	stateMachine = machine;
	interfaceElements.push_back(InterfaceElement( ScreenObject ("startButton", assets, sf::Vector2f(550,300), float(1)), Action ( [machine]{  machine->changeState(std::make_shared<PlayingState>());})));
	interfaceElements.push_back(InterfaceElement( ScreenObject ("editButton", assets, sf::Vector2f(150,300),float(0.35)), Action ( [machine]{ machine->changeState(std::make_shared<EditingState>());})));
	interfaceElements.push_back(InterfaceElement( ScreenObject ("settingButton", assets, sf::Vector2f(0,0), float(0.3)), Action( [machine] {machine->changeState(std::make_shared<SettingsState>());})));
	interfaceElements.push_back(InterfaceElement( ScreenObject ("settingButton", assets, sf::Vector2f(-1,-1), float(0)), Action( [machine] {machine->changeState(std::make_shared<PauseState>());})));

}

void Interface::goToPauseMenu(sf::View & view){ 
	pauseElements.push_back(InterfaceElement( ScreenObject ("settingButton", assets, sf::Vector2f(100, 200), float(0.4)), Action( [this] {stateMachine->changeState(std::make_shared<MenuState>());})));
	pauseElements.push_back(InterfaceElement( ScreenObject ("startButton", assets, sf::Vector2f(400, 200), float(1)), Action( [this] {stateMachine->changeState(stateMachine->getCurrentState());})));
	interfaceElements[3].changeState();
	//view.setCenter(sf::Vector2f(view.getSize().x / 2, view.getSize().y / 2));

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
				pauseElements.pop_back();
			}
			// Back to previous state
			if(event.type == sf::Event::MouseButtonPressed && element.comparePosition(sf::Vector2f(position.x+900,position.y+440))){		
				std::cout<<"go back\n";
				pauseGame = false;
				element.changeState();
				pauseElements.pop_back();

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