/// @file
#include <iostream>
#include "Player.hpp"

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

AnimatedPlayerGraphics::AnimatedPlayerGraphics(const std::string & assetName, AssetManager & assets, SpriteCharacter & characterData):
	AnimatedGraphicsComponent(assetName, assets, characterData)
{}

void AnimatedPlayerGraphics::processViewChanges(sf::View & view, const sf::Vector2f & position){
	if(position.y < 300){
		view.setCenter(sf::Vector2f(position.x, position.y));
	} else {
		view.setCenter(sf::Vector2f(position.x, 300));
	}
}

PlayerGraphics::PlayerGraphics(const std::string & assetName, AssetManager & assets):
	GraphicsComponent(assetName, assets)
{}

void PlayerInput::processInput(const sf::Vector2f & position, sf::Vector2f & direction, std::array< KeyBinding, 3 > & keys){
	direction.x = 0;	//Stand still
	direction.y = 0;
	if(sf::Keyboard::isKeyPressed(keys[0].getKey())){
		direction.x = -1;
	}
	if(sf::Keyboard::isKeyPressed(keys[1].getKey())){
		direction.x = 1;
	}
	if(sf::Keyboard::isKeyPressed(keys[2].getKey())){
		direction.y = -1;
	}
}



void PlayerInput::processItemUsage(std::vector<std::shared_ptr<Item>> & items, Character * ownCharacter){
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		if(items.at(ownCharacter->getSelectedItem())->use(ownCharacter, characters)){			//If item is broken
			items.erase(std::find(items.begin(), items.end(), items.at(ownCharacter->getSelectedItem())));
			ownCharacter->getSelectedItem()--;
		}
	}
}

void PlayerInput::handleEvent(const sf::Event & event, int_fast16_t & selectedItem){
	if(event.type == sf::Event::MouseWheelMoved){	
		selectedItem += event.mouseWheel.delta;
	}
}
