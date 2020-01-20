#include "Interface.hpp"

Interface::Interface(Game & game, AssetManager & assets, sf::RenderWindow & window):
	game(game),
	window(window)
{
	background.setTexture(assets.getTexture("background"));
	interfaceElements.push_back(sf::Sprite(assets.getTexture("startButton")));
	interfaceElements[0].setPosition(550, 300);
	interfaceElements.push_back(sf::Sprite(assets.getTexture("editButton")));
	interfaceElements[1].setPosition(150, 300);
	interfaceElements[1].setScale(0.35, 0.35);
}

void Interface::handleInput(const sf::Event & event){
	if(state == states::DISPLAYING){
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
			game.startWorld("World/world.txt");
			state = states::IDLE;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
			game.editWorld("World/world.txt");
			state = states::IDLE;
		}
		for(const sf::Sprite & sprite : interfaceElements){
			if(sprite.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))){
				if(event.type == sf::Event::MouseButtonPressed && sprite.getPosition() == sf::Vector2f(550, 300)){
					game.startWorld("World/world.txt");
					state = states::IDLE;
				}
				if(event.type == sf::Event::MouseButtonPressed && sprite.getPosition() == sf::Vector2f(150, 300)){
					game.editWorld("World/world.txt");
					state = states::IDLE;
				}
			}
		}
	}
}


void Interface::display(){
	switch(state){
		case states::DISPLAYING: {
			window.draw(background);
			for(const sf::Sprite & sprite : interfaceElements){
				window.draw(sprite);
			}
			break;
		}
		default: {
			break;
		}
	}
}