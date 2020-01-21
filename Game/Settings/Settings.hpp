/// @file

#ifndef _SETTINGS_HPP
#define _SETTINGS_HPP

#include <SFML/Graphics.hpp>
#include <array>
#include "StateMachine.hpp"
#include "bindings.hpp"
#include "keybinding.hpp"
#include "tekst.hpp"

class StateMachine;
//class Bindings;

enum class StateSettings
{
    IDLE,
    CHANGEKEY
};

class Settings {
private:
	sf::RenderWindow & window;
	StateSettings state = StateSettings::IDLE;
	uint selectedKey = 0;			//holds the index of the array Bindings, needed to select a key if pressed on it
	Text backButton = { "Back", sf::Vector2f{50.0, 440.0}, 1.0, sf::Color::Red};		//seperate backButton object for going back to menu screen
	sf::Sprite background;

public:
	Settings( sf::RenderWindow & window, AssetManager & assets );

	void handleInput();

	void handleEvent( const sf::Event & event, StateMachine * machine );

	void draw();

};

#endif
