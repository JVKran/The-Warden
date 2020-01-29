/// @file
#ifndef __INTERFACE_ELEMENT_HPP
#define __INTERFACE_ELEMENT_HPP

#include "ScreenObject.hpp"
#include "Action.hpp"
/// \brief
/// InterfaceElement
/// \details
/// This class is the entire InterfaceElement. It will handle the ScreenObject and an action.
/// This will check whether you've clicked on a ScreenObject in the right position and change the state if you do.
class InterfaceElement {
	private:
		ScreenObject element;
		Action action;
	public:
		InterfaceElement( ScreenObject element, Action action );

		bool comparePosition( sf::Vector2f position );
		bool contains( sf::RenderWindow & window, sf::View & view );

		void changeState();

		void setPosition(const sf::Vector2f & position);

		void draw( sf::RenderWindow & window );
	};
#endif