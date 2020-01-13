#include "ScreenObject.hpp"

ScreenObject::ScreenObject(const std::string & assetName, AssetManager & assets, const sf::Vector2f & position){
	sprite.setTexture(assets.getTexture(assetName));
	sprite.setPosition(position);
}

void ScreenObject::draw(sf::RenderWindow & window){
	window.draw(sprite);
}