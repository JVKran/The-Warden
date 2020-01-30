/// @file
#include "InterfaceElement.hpp"

/// \brief
/// InterfaceElement constructor.
/// \details
/// This creates an InterfaceElement. 
/// @param work The lambda to execute when the element is clicked.
/// @param assetName The name of the texture to get from the AssetManager that should be used to construct te sprite.
/// @param assets The AssetManager to use to retrieve assets.
/// @param position The initial position to set and draw the sprite.
/// @param scale The initial scale of the sprite.
/// @param rotation The initial rotation of the sprite.
/// @param windowLayer The initial window layer the sprite is part of in the world.
InterfaceElement::InterfaceElement(std::function< void() > work, const std::string & assetName, AssetManager & assets, const sf::Vector2f & position, const float scale, const float rotation, const int windowLayer ):
	ScreenObject(assetName, assets, position, scale, rotation, windowLayer),
	work(work)
{}

/// \brief
/// Compare positions.
/// \details
/// This will compare the positions of the element and the given position and return true when the positions are the same.
/// \return A bool that returns true when the positions are the same.
/// @param position The position to compare.
bool InterfaceElement::comparePosition( sf::Vector2f position ){
	return getPosition() == position;
}

/// \brief
/// Mouse contained.
/// \details
/// This function will check whether your mouse is inside the element.
/// \return A bool that depends on whether your mouse is inside the element.
/// @param window The sf::RenderWindow to use for converting the relative position to the absolute clicked position.
/// @param view The sf::View to use for converting the relative position to the absolute clicked position.
bool InterfaceElement::contains( sf::RenderWindow & window , sf::View & view){;
	return getBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(), view));
}

/// \brief
/// Start given function.
/// \details
/// This function will start the given lambda function.
void InterfaceElement::changeState(){ 
	work();
}