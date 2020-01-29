#include "InterfaceElement.hpp"

InterfaceElement::InterfaceElement( ScreenObject element, std::function< void() > work):
	element(element),
	work(work)
{}

bool InterfaceElement::comparePosition( sf::Vector2f position ){
	return element.getPosition() == position;
}

bool InterfaceElement::contains( sf::RenderWindow & window , sf::View & view){;

	return element.getBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(), view));
}

void InterfaceElement::changeState(){ 
	work();
}

void InterfaceElement::setPosition(const sf::Vector2f& position){
	element.setPosition(position);
}

void InterfaceElement::draw( sf::RenderWindow & window ){
	element.draw(window);
}