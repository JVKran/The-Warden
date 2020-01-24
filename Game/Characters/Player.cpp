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

/// \brief
/// Adds a tile in the world
/// \details
/// This is called by the game, it adds a new tile in the vector tiles in the world,
/// on the location of the mouse in the window's view (so not the normal pixel locations)
/// the new tile is a 'crate' object
void PlayerInput::addTile(const sf::Event & event, World & world, sf::RenderWindow & window, sf::View & view){
	sf::Vector2f position = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);		//gets to position based on the mouse coordinates in a view
	world.addTile("crate", position);
}

/// \brief
/// Deletes a tile in the world
/// \details
/// This is called by the game, and it deletes the object where the mouse is located on.
/// The mouse position is called by mapPixelToCoords which uses view to get the right location
/// and not the mouse window location.
void PlayerInput::deleteTile(const sf::Event & event, World & world, sf::RenderWindow & window, sf::View & view){
	std::vector<Tile> & objects = world.getTiles();
	for(Tile & object : objects){
		if(object.getBounds().contains(sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window), view)))){
				objects.erase( std::find(objects.begin(), objects.end(), object) );
		}
	}
}

void PlayerInput::processItemUsage(std::vector<std::shared_ptr<Item>> & items, Character * ownCharacter){
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		if(items.at(ownCharacter->getSelectedItemNumber())->use(ownCharacter, characters)){			//If item is broken
			items.erase(std::find(items.begin(), items.end(), items.at(ownCharacter->getSelectedItemNumber())));
			ownCharacter->getSelectedItemNumber()--;
		}
		if(ownCharacter->getSelectedItem()->isWeapon()){
			ownCharacter->getGraphics()->setFightAnimation();
		}
	}
}

void PlayerInput::handleEvent(const sf::Event & event, int_fast16_t & selectedItem){
	if(event.type == sf::Event::MouseWheelMoved){	
		selectedItem += event.mouseWheel.delta;
	}
}
