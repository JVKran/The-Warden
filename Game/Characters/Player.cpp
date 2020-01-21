/// @file

#include "Player.hpp"

PlayerGraphics::PlayerGraphics(const std::string & assetName, AssetManager & assets):
	GraphicsComponent(assetName, assets)
{}

void PlayerInput::processInput(const sf::Vector2f & velocity, const sf::Vector2f & position, sf::Vector2f & direction, std::vector<Character> & characters, std::vector<std::shared_ptr<Item>> & items, Character * ownCharacter){
	direction.x = 0;	//Stand still
	direction.y = 0;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		direction.x = -1;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		direction.x = 1;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
		direction.y -=1;
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