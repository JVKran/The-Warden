/// @file
#include "InterfaceElement.hpp"
/// \brief
/// Create an instance.
/// \details
/// This creates an InterFaceElement. 
/// @param element A ScreenObject to make and check the sprites.
/// @param action An Action to store lambda functions.
InterfaceElement::InterfaceElement( ScreenObject element, Action action ):
	element(element),
	action(action)
{}

/// \brief
/// Compare positions.
/// \details
/// This will compare the positions of the element and the given position.
/// \return A bool that depends on whether the positions are the same.
bool InterfaceElement::comparePosition( sf::Vector2f position ){
	return element.getPosition() == position;
}
/// \brief
/// Mouse contained.
/// \details
/// This function will check whether your mouse is inside the element.
/// \return A bool that depends on whether your mouse is inside the element.
bool InterfaceElement::contains( sf::RenderWindow & window , sf::View & view){;
	return element.getBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(), view));
}
/// \brief
/// Start given function.
/// \details
/// This function will start the given lambda function.
void InterfaceElement::changeState(){ 
	action.startFunction();
}
/// \brief
/// Set position.
/// \details
/// This function will set the element's position to the given position.
void InterfaceElement::setPosition(const sf::Vector2f& position){
	element.setPosition(position);
}
/// \brief
/// Draw element.
/// \details
/// Draw the element in the window.
void InterfaceElement::draw( sf::RenderWindow & window ){
	element.draw(window);
}