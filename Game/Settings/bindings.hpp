#ifndef _BINDINGS_HPP
#define _BINDINGS_HPP

#include <array>
#include "keybinding.hpp"
#include "tekst.hpp"

inline std::array< KeyBinding, 3 > Bindings { 
	KeyBinding ( "Left", 		sf::Keyboard::Left,  		Text( "Left : Left", 	sf::Vector2f{500.0, 50.0}, 	1.0, sf::Color::Red, 1 )	),
	KeyBinding ( "Right",		sf::Keyboard::Right, 		Text( "Right : Right", 	sf::Vector2f{500.0, 80.0}, 	1.0, sf::Color::Red, 1 )	),
	KeyBinding ( "Jump", 		sf::Keyboard::Space, 		Text( "Jump : Space", 	sf::Vector2f{500.0, 110.0}, 1.0, sf::Color::Red, 1 )	)
};

#endif