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

enum class StateSettings
{
    IDLE,
    CHANGEKEY
};

/// \brief
/// Settings screen
/// \details
/// This class features the ability to change the keybindings for the character
class Settings {
private:
	sf::RenderWindow & window;
	StateSettings state = StateSettings::IDLE;											//!< The current state of the class
	uint selectedKey = 0;																//!< holds the index of the array Bindings, needed to select a key if pressed on it
	Text backButton = { "Back", sf::Vector2f{50.0, 440.0}, 1.0, sf::Color::Red};		//!< seperate backButton object for going back to menu screen.
	sf::Sprite background;																//!< sprite object to give a nice background on the screen

public:

	/// \brief
	/// Default constructor
	/// \details
	/// This is the constructor of the class.
	/// It requires a window to draw on and assets to make the background.
	Settings( sf::RenderWindow & window, AssetManager & assets );

	/// \brief
	/// Handles default input
	/// \details
	/// This function handles the default inputs, not the event inputs
	void handleInput();

	/// \brief
	/// Handles the event input
	/// \details
	/// This function handles the input from the events
	void handleEvent( const sf::Event & event, StateMachine * machine );

	/// \brief
	/// Draws the objects
	/// \details
	/// Draws all the objects of this class.
	void draw();

};

#endif
