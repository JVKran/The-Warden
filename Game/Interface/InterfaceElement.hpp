/// @file
#ifndef __INTERFACE_ELEMENT_HPP
#define __INTERFACE_ELEMENT_HPP
#include <functional>
#include "ScreenObject.hpp"
/// \brief
/// InterfaceElement
/// \details
/// This class is the entire InterfaceElement. It will handle the ScreenObject and a lambda.
/// This will check whether you've clicked on a ScreenObject in the right position and change the state if you do.
class InterfaceElement {
	private:
		ScreenObject element;
		std::function< void() > work;
	public:
		InterfaceElement( ScreenObject element, std::function< void() > work);

		bool comparePosition( sf::Vector2f position );
		bool contains( sf::RenderWindow & window, sf::View & view );

		void changeState();

		void setPosition(const sf::Vector2f & position);

		void draw( sf::RenderWindow & window );
	};
#endif