#include "ScreenObject.hpp"

ScreenObject::ScreenObject(const std::string & assetName, AssetManager & assets){
	sprite.setTexture(assets.getTexture(assetName));
}

void ScreenObject::draw(sf::RenderWindow & window){
	window.draw(sprite);
}