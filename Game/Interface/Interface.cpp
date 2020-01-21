#include "Interface.hpp"

Interface::Interface(Game & game,  Editor & editor, AssetManager & assets, sf::RenderWindow & window):
	game(game),
	editor(editor),
	window(window)
{
	background.setTexture(assets.getTexture("background"));
	
	ScreenObject test("startButton", assets, sf::Vector2f(550,300), float(1));
	ScreenObject test2("editButton", assets, sf::Vector2f(150,300),float(0.35));
	
	Action act([machine]{  machine->changeState(std::make_shared<PlayingState>());});
	Action act2( [machine]{ machine->changeState(std::make_shared<EditingState>());});
	
	interfaceElements.push_back(InterfaceElement( test, act));
	interfaceElements.push_back(InterfaceElement( test2, act2));
	/*interfaceElements.push_back(sf::Sprite(assets.getTexture("startButton")));
	interfaceElements[0].setPosition(550, 300);
	interfaceElements.push_back(sf::Sprite(assets.getTexture("editButton")));
	interfaceElements[1].setPosition(150, 300);
	interfaceElements[1].setScale(0.35, 0.35);*/
}

void Interface::handleInput(StateMachine * machine){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
		game.startWorld("World/world.txt");
		interfaceElements[0].changeState();
		//game.startWorld("World/world.txt");
		//machine->changeState(std::make_shared<PlayingState>());
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
		 editor.selectWorld("World/world.txt");
		interfaceElements[1].changeState();/*
		editor.selectWorld("World/world.txt");
		machine->changeState(std::make_shared<EditingState>());*/
	}
}

void Interface::handleEvent(const sf::Event & event, StateMachine * machine){
	for( InterfaceElement & sprite : interfaceElements){
		if(sprite.contains(window)){
		//if(sprite.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))){
			if(event.type == sf::Event::MouseButtonPressed && sprite.comparePosition(sf::Vector2f(550, 300)) ){
				game.startWorld("World/world.txt");
				sprite.changeState();
				/*game.startWorld("World/world.txt");
				machine->changeState(std::make_shared<PlayingState>());*/
			}
			if(event.type == sf::Event::MouseButtonPressed && sprite.comparePosition(sf::Vector2f(150, 300)) ){
						 editor.selectWorld("World/world.txt");
				sprite.changeState();/*
				editor.selectWorld("World/world.txt");
				machine->changeState(std::make_shared<EditingState>());*/
			}
		}
	}
}


void Interface::display(){
	window.draw(background);
	for( InterfaceElement & sprite : interfaceElements){
		sprite.draw(window);
	}
}