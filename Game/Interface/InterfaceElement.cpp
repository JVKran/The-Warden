/// @file
#include "InterfaceElement.hpp"

/// \brief
/// InterfaceElement constructor.
/// \details
/// This creates an InterfaceElement. 
/// @param work Store lambda functions.
InterfaceElement::InterfaceElement(std::function< void() > work, const std::string & assetName, AssetManager & assets, const sf::Vector2f & position, const float scale, const float rotation, const int windowLayer ):
	ScreenObject(assetName, assets, position, scale, rotation, windowLayer),
	work(work)
{}

/// \brief
/// Compare positions.
/// \details
/// This will compare the positions of the element and the given position and return true when the positions are the same.
/// \return A bool that depends on whether the positions are the same.
bool InterfaceElement::comparePosition( sf::Vector2f position ){
	return getPosition() == position;
}

/// \brief
/// Mouse contained.
/// \details
/// This function will check whether your mouse is inside the element.
/// \return A bool that depends on whether your mouse is inside the element.
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