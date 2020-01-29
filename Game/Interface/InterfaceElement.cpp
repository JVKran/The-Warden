#include "InterfaceElement.hpp"

InterfaceElement::InterfaceElement(std::function< void() > work, const std::string & assetName, AssetManager & assets, const sf::Vector2f & position, const float scale, const float rotation, const int windowLayer ):
	ScreenObject(assetName, assets, position, scale, rotation, windowLayer),
	work(work)
{}

bool InterfaceElement::comparePosition( sf::Vector2f position ){
	return getPosition() == position;
}

bool InterfaceElement::contains( sf::RenderWindow & window , sf::View & view){;

	return getBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(), view));
}

void InterfaceElement::changeState(){ 
	work();
}
