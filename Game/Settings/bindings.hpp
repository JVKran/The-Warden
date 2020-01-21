#ifndef _BINDINGS_HPP
#define _BINDINGS_HPP

#include <array>
#include "keybinding.hpp"
#include "tekst.hpp"

static std::array< KeyBinding, 5 > Bindings { 
	KeyBinding ( "Left", 		sf::Keyboard::A,  		Text( "Left : A", 		sf::Vector2f{500.0, 50.0}, 	1.0, sf::Color::Red, 1 )	),
	KeyBinding ( "Right",		sf::Keyboard::D, 		Text( "Right : D", 		sf::Vector2f{500.0, 80.0}, 	1.0, sf::Color::Red, 1 )	),
	KeyBinding ( "Up", 			sf::Keyboard::W, 		Text( "Up : W", 		sf::Vector2f{500.0, 110.0}, 1.0, sf::Color::Red, 1 )	),
	KeyBinding ( "Down", 		sf::Keyboard::S, 	 	Text( "Down : S", 		sf::Vector2f{500.0, 140.0}, 1.0, sf::Color::Red, 1 )	),
	KeyBinding ( "Jump", 		sf::Keyboard::Space, 	Text( "Jump : Space", 	sf::Vector2f{500.0, 170.0}, 1.0, sf::Color::Red, 1 )	)
};

#endif