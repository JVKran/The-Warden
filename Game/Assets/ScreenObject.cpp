/// @file

#include "ScreenObject.hpp"

bool operator<(sf::Vector2f lhs, sf::Vector2f rhs){
	return lhs.x < rhs.x;
}

/// \brief
/// Create instance.
/// \details
/// This function creates a ScreenObject.
/// @param assetName The name of the texture to get from the AssetManager that should be used to construct te sprite.
/// @param assets The AssetManager to use to retrieve assets.
/// @param position The initial position to set and draw the sprite.
/// @param scale The initial scale of the sprite.
/// @param collidable The initial collidability with Character types.
ScreenObject::ScreenObject(const std::string & assetName, AssetManager & assets, const sf::Vector2f & position, const float scale, const float rotation, const int windowLayer):
	assetName(assetName),
	windowLayer(windowLayer)
{
	sprite.setTexture(assets.getTexture(assetName));
	sprite.setPosition(position);
	sprite.setScale(scale, scale);
	sprite.setRotation(rotation);
}

/// \brief
/// Get configuration.
/// \details
/// This function gathers all data from this ScreenObject and returns it in a readable and storeable format.
/// \return A string with all configuration variables in format: "(x,y) assetName collidability scale".
std::string ScreenObject::getConfiguration() const {
	return (getPositionString(sprite.getPosition()) + ' ' + assetName + ' ' + ' ' + std::to_string(sprite.getScale().x) + ' ' + std::to_string(sprite.getRotation()) + ' ' + std::to_string(windowLayer));
}

/// \brief
/// Get object name.
/// \return The name of the tile; equal to the texture and assetname.
std::string ScreenObject::getName() const{
	return assetName;
}

/// \brief
/// Draw object.
/// \details
/// This function draws itself in the passed window.
/// @param window The RenderWindow to draw the sprite in.
void ScreenObject::draw(sf::RenderWindow & window) const {
	window.draw(sprite);
}

/// \brief
/// Set new sprite scale.
/// \details
/// This function sets the new scale of the sprite.
/// @param newScale The scale the sprite should have from now on.
void ScreenObject::setNewScale(const float newScale){
	sprite.setScale(sf::Vector2f(newScale, newScale));
}

/// \brief
/// Get sprite scale.
/// \return The current scale of the sprite.
sf::Vector2f ScreenObject::getScale() const {
	return sprite.getScale();
}

/// \brief
/// Get position.
/// \return The current position of the sprite.
sf::Vector2f ScreenObject::getPosition() const {
	return sprite.getPosition();
}

/// \brief
/// Set position.
/// \details
/// Sets the position of the sprite to a new position.
/// @param newPostion The new position of the sprite.
void ScreenObject::setPosition(const sf::Vector2f & newPosition){
	sprite.setPosition(newPosition);
}

/// \brief
/// Set rotation.
/// \details
/// Sets the rotations of the sprite to a new angle.
/// @param angle The new angle of the sprite.
void ScreenObject::setRotation(const float angle){
	sprite.setRotation(angle);
}

/// \brief
/// Get rotation.
/// \returns The current angle of the sprite.
float ScreenObject::getRotation() const {
	return sprite.getRotation();
}

/// \brief
/// Get global bounds.
/// \return The global bounds of the sprite.
sf::FloatRect ScreenObject::getBounds() const {
	return(sprite.getGlobalBounds());
}

/// \brief
/// Create instance.
/// \details
/// This function creates a Tile which is a subclass of ScreenObject that's also selectable.
/// @param assetName The name of the texture to get from the AssetManager that should be used to construct te sprite.
/// @param assets The AssetManager to use to retrieve assets.
/// @param position The initial position to set and draw the sprite.
/// @param scale The initial scale of the sprite.
/// @param collidable The initial collidability with Character types.
Tile::Tile(const std::string & assetName, AssetManager & assets, const sf::Vector2f & position, const float scale, const bool collidable, const float rotation, const int windowLayer):
	ScreenObject(assetName, assets, position, scale, rotation, windowLayer),
	collidable(collidable)
{}

bool Tile::isPartOfWorld() const{
	return hasBeenAdded;
}

void Tile::makePartOfWorld(const bool & added){
	hasBeenAdded = added;
}

/// \brief
/// Get configuration.
/// \details
/// This function gathers all data from this ScreenObject and returns it in a readable and storeable format.
/// \return A string with all configuration variables in format: "(x,y) assetName collidability scale".
std::string Tile::getConfiguration() const {
	return (getPositionString(sprite.getPosition()) + ' ' + assetName + ' ' + std::to_string(collidable) + ' ' + std::to_string(sprite.getScale().x) + ' ' + std::to_string(sprite.getRotation()) + ' ' + std::to_string(windowLayer));
}

/// \brief
/// Get collidability.
/// \details
/// This function returns wether or not Character types should collide with this object.
/// \return Wether or not Character types should collide with this object.
bool Tile::isCollidable() const{
	return collidable;
}

/// \brief
/// Set collidability.
/// \details
/// This function sets collidability to the desired functioning.
/// @param newCollidable Wether or not Character types should collide with this object from now on.
void Tile::setCollidable(const bool newCollidable){
	collidable = newCollidable;
}

bool Tile::isInteractable() const{
	return interactable;
}

void Tile::setInteractability(const bool newInteractability){
	interactable = newInteractability;
}

bool Tile::isPassageWay() const{
	return passageWay;
}

void Tile::setPassageWay(const bool newPassageWay){
	passageWay = newPassageWay;
}

bool Tile::isPassageEntrance() const{
	return passageEntrance;
}

void Tile::changePassageEntrance(const bool newPassageEntrance){
	passageEntrance = newPassageEntrance;
}

/// \brief
/// Set mouse following.
/// \details
/// Enables the Sprite to follow the position of the mouse.
/// @param follow Wether or not the sprite should follow the cursor.
bool Tile::setFollowMouse(const bool follow){
	if(followMouse != follow){
		followMouse = follow;
		return true;
	}
	return false;
}

/// \brief
/// Is following mouse?
/// \return Wether or not the sprite is following the position of the mouse.
bool Tile::isFollowingMouse() const {
	return followMouse;
}

/// \brief
/// Move to position.
/// \details
/// This functions sets the position of the sprite to the passed position.
/// @param position The position to move the sprite to.
void Tile::move(const sf::Vector2f & position){
	if(followMouse){
		sprite.setPosition(sf::Vector2f(position.x - sprite.getGlobalBounds().width / 2, position.y +- sprite.getGlobalBounds().height / 2));
	}
}

/// \brief
/// Assignment operator.
/// \details
/// This functions assigns the passed object to itself.
/// @param lhs Tile to copy.
/// \return Refrence to itself.
Tile& Tile::operator=(Tile lhs){
	if(&lhs != this){
		followMouse = lhs.followMouse;
		assetName = lhs.assetName;
		sprite = lhs.sprite;
		collidable = lhs.collidable;
	}
	return *this;
}

/// \brief
/// Equality operator.
/// \details
/// This function checks for equality of the positions of both Tile objects.
/// @param lhs Tile to compare.
/// \return Wether or not the positions are equal.
bool Tile::operator==(Tile lhs) const {
	return sprite.getPosition().x == lhs.sprite.getPosition().x;
}

/// \brief
/// Smaller than operator.
/// \details
/// This function checks wether or not its position is smaller than that of the passed object.
/// @param lhs Tile to compare.
/// \return Wether or not the position is smaller than the position of the passed object.
bool Tile::operator<(Tile lhs) const {
	return sprite.getPosition().x < lhs.sprite.getPosition().x;
}
