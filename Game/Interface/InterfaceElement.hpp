#ifndef __INTERFACE_ELEMENT_HPP
#define __INTERFACE_ELEMENT_HPP

#include "ScreenObject.hpp"
#include "Action.hpp"

class InterfaceElement {
	private:
		ScreenObject element;
		Action action;
	public:
		InterfaceElement( ScreenObject element, Action action );

		bool comparePosition( sf::Vector2f position );

		bool contains( sf::RenderWindow & window );

		void changeState();

		void draw( sf::RenderWindow & window );
	};
#endif