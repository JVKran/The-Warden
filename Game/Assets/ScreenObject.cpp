#include "ScreenObject.hpp"

ScreenObject::ScreenObject(const std::string & assetName, AssetManager & assets, const sf::Vector2f & position, const float scale){
	sprite.setTexture(assets.getTexture(assetName));
	sprite.setPosition(position);
	sprite.setScale(scale, scale);
}

void ScreenObject::draw(sf::RenderWindow & window){
	window.draw(sprite);
}

sf::Vector2f ScreenObject::getPosition() const {
	return sprite.getPosition();
}