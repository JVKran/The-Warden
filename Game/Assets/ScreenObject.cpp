#include "ScreenObject.hpp"

bool operator<(sf::Vector2f lhs, sf::Vector2f rhs){
	return lhs.x < rhs.x;
}

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

sf::FloatRect ScreenObject::getBounds() const {
	return(sprite.getGlobalBounds());
}

SelectableObject::SelectableObject(const std::string & assetName, AssetManager & assets, const sf::Vector2f & position, const float scale):
	ScreenObject(assetName, assets, position, scale)
{}

bool SelectableObject::setFollowMouse(const bool follow){
	if(followMouse != follow){
		followMouse = follow;
		return true;
	}
	return false;
}

bool SelectableObject::isFollowingMouse() const {
	return followMouse;
}

void SelectableObject::setNewScale(const float newScale){
	sprite.setScale(sf::Vector2f(newScale, newScale));
}

void SelectableObject::move(const sf::Vector2i & position){
	if(followMouse){
		sprite.setPosition(sf::Vector2f(position.x - sprite.getGlobalBounds().width / 2, position.y +- sprite.getGlobalBounds().height / 2));
	}
}

SelectableObject& SelectableObject::operator=(SelectableObject lhs){
	if(&lhs != this){
		followMouse = lhs.followMouse;
	}
	return *this;
}

bool SelectableObject::operator==(SelectableObject lhs){
	return sprite.getPosition() == lhs.sprite.getPosition();
}

bool SelectableObject::operator<(SelectableObject lhs) const {
	return sprite.getPosition() < lhs.sprite.getPosition();
}
