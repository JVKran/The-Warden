/// @file
#ifndef __INTERFACE_ELEMENT_HPP
#define __INTERFACE_ELEMENT_HPP
#include <functional>
#include "ScreenObject.hpp"

/// \brief
/// InterfaceElement
/// \details
/// This class is the entire InterfaceElement; it's responsible for executing actions when it is clicked.
class InterfaceElement : public ScreenObject{
	private:
		std::function< void() > work;			//!< The function that should execute when the element is clicked.
	public:
		InterfaceElement(  std::function< void() > work, const std::string & assetName, AssetManager & assets, const sf::Vector2f & position = sf::Vector2f(0,0), const float scale = 1,const float rotation = 0, const int windowLayer = 0);

		bool comparePosition( sf::Vector2f position );
		bool contains( sf::RenderWindow & window, sf::View & view );

		void changeState();
	};
#endif