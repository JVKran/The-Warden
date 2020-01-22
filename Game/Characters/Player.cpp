/// @file

#include "Player.hpp"
#include <iostream>
PlayerGraphics::PlayerGraphics(const std::string & assetName, AssetManager & assets):
	GraphicsComponent(assetName, assets)
{}

void PlayerInput::processInput(const sf::Vector2f & position, sf::Vector2f & direction){
	direction.x = 0;	//Stand still
	direction.y = 0;
	if(sf::Keyboard::isKeyPressed(Bindings[0].getKey())){
		direction.x = -1;
	}
	if(sf::Keyboard::isKeyPressed(Bindings[1].getKey())){
		direction.x = 1;
	}
	if(sf::Keyboard::isKeyPressed(Bindings[2].getKey())){
		direction.y -=1;
	}
	if(sf::Keyboard::isKeyPressed(Bindings[3].getKey())){
		// checkInteraction();
	}
}

void PlayerInput::processItemUsage(std::vector<std::shared_ptr<Item>> & items, Character * ownCharacter){
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		items.at(0)->use(ownCharacter, characters);
	}
}
/// \brief
/// Draw the Character.
/// \details
/// This function draws the Characte in the RenderWindow and sets the View to the position
/// of the Character to keep the player centered.
void PlayerGraphics::processGraphics(sf::RenderWindow & window, const sf::Vector2f & position, sf::View & view){
	sprite.setPosition(position);
	if(position.y < 300){
		view.setCenter(sf::Vector2f(position.x, position.y));
	} else {
		view.setCenter(sf::Vector2f(position.x, 300));
	}
	window.draw(sprite);
}

sf::Vector2f PlayerGraphics::getDimensions(){
	return sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
}