/// @file

#ifndef _SETTINGS_HPP
#define _SETTINGS_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include <memory>
#include "StateMachine.hpp"
#include "bindings.hpp"
#include "keybinding.hpp"
#include "tekst.hpp"

class StateMachine;
class Bindings;

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

public:
	Settings( sf::RenderWindow & window );

	void handleInput( const sf::Event & event, StateMachine * machine );

};

#endif
