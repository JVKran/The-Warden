#include "ScreenObject.hpp"

std::string getPositionString(const sf::Vector2f & positionToPrint) {
	return("(" + std::to_string(static_cast<int>(positionToPrint.x)) + "," + std::to_string(static_cast<int>(positionToPrint.y)) + ")");
}

ScreenObject& ScreenObject::operator=(ScreenObject lhs){
	if(&lhs != this){
		sf::Sprite tempSprite = sprite;
		sprite = lhs.sprite;
		lhs.sprite = tempSprite;
		std::string tempName = assetName;
		assetName = lhs.assetName;
		lhs.assetName = tempName;
	}
	return *this;
}

ScreenObject::ScreenObject(const std::string & assetName, AssetManager & assets, const sf::Vector2f & position, const float scale):
	assetName(assetName)
{
	sprite.setTexture(assets.getTexture(assetName));
	sprite.setPosition(position);
	sprite.setScale(scale, scale);
}

std::string ScreenObject::getConfiguration() const {
	return (getPositionString(sprite.getPosition()) + ' ' + assetName + ' ' + std::to_string(sprite.getScale().x));
}

void ScreenObject::draw(sf::RenderWindow & window){
	window.draw(sprite);
}

sf::Vector2f ScreenObject::getPosition() const {
	return sprite.getPosition();
}

sf::FloatRect ScreenObject::getBounds(){
	return(sprite.getGlobalBounds());
}