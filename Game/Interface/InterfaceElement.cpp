#include "InterfaceElement.hpp"

InterfaceElement::InterfaceElement( ScreenObject element, Action action ):
	element(element),
	action(action)
{}

bool InterfaceElement::comparePosition( sf::Vector2f position ){
	return element.getPosition() == position;
}

bool InterfaceElement::contains( sf::RenderWindow & window ){
	return element.getBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
}

void InterfaceElement::changeState(){ 
	action.startFunction();
}

void InterfaceElement::draw( sf::RenderWindow & window ){
	element.draw(window);
}