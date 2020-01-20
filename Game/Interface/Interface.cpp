#include "Interface.hpp"

Interface::Interface(Game & game, Editor & editor, AssetManager & assets, sf::RenderWindow & window):
	game(game),
	editor(editor),
	window(window)
{
	background.setTexture(assets.getTexture("background"));
	interfaceElements.push_back(sf::Sprite(assets.getTexture("startButton")));
	interfaceElements[0].setPosition(550, 300);
	interfaceElements.push_back(sf::Sprite(assets.getTexture("editButton")));
	interfaceElements[1].setPosition(150, 300);
	interfaceElements[1].setScale(0.35, 0.35);
}

void Interface::handleInput(const sf::Event & event, StateMachine * machine){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
		game.startWorld("World/world.txt");
		machine->changeState(std::make_shared<PlayingState>());
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
		editor.selectWorld("World/world.txt");
		machine->changeState(std::make_shared<EditingState>());
	}
	for(const sf::Sprite & sprite : interfaceElements){
		if(sprite.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))){
			if(event.type == sf::Event::MouseButtonPressed && sprite.getPosition() == sf::Vector2f(550, 300)){
				game.startWorld("World/world.txt");
				machine->changeState(std::make_shared<PlayingState>());
			}
			if(event.type == sf::Event::MouseButtonPressed && sprite.getPosition() == sf::Vector2f(150, 300)){
				editor.selectWorld("World/world.txt");
				machine->changeState(std::make_shared<EditingState>());
			}
		}
	}
}


void Interface::display(){
	window.draw(background);
	for(const sf::Sprite & sprite : interfaceElements){
		window.draw(sprite);
	}
}