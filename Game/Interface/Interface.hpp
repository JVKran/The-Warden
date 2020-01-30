/// @file
#ifndef __INTERFACE_HPP
#define __INTERFACE_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include <memory>
#include "Game.hpp"
#include "Settings.hpp"
#include "StateMachine.hpp"
#include "InterfaceElement.hpp"
#include "ScreenObject.hpp"
#include "World.hpp"
#include "States.hpp"

class State;
class Game;
class StateMachine;
class Settings;

/// \brief
/// Interface
/// \details
/// This class is responsible for the user interface. This consists of drawing the main menu, pause menu, handling input
/// in these menu's and handling some basic inputs when outside menu's.
class Interface {
	private:
		Game & game;					//!< The Game to start, pause and stop.
		Editor & editor;				//!< The Editor to start, pause and stop.
		AssetManager & assets;			//!< The AssetManager to use for gathering the needed textures.
		Settings & settings;			//!< The Settings to use for determining the actions bound to the key.
		StateMachine * machine;			//!< The StateMachine to use for changing the current state.
		World world;

		sf::RenderWindow & window;		//!< The RenderWindow to draw the Interface in.

		bool pauseGame = false;			//!< Wether or not the Game is paused.

		sf::Sprite background;			//!< The Background to draw when the main menu is active.

		std::vector<InterfaceElement> interfaceElements;		//!< A std::vector with all InterfaceElement objects used for the menu.
		std::vector<InterfaceElement> pauseElements;			//!< A std::vector with all InterfaceElement objects used for the pause state.

		sf::RectangleShape pauseBackground;						//!< The background to show in the pause state.
		std::shared_ptr<State> prevState;						//!< The previous state of the State Machine.
	public:
		Interface(Game & game, Editor & editor, Settings & settings, AssetManager & assets, sf::RenderWindow & window);

		void initialize(StateMachine * newMachine);
		void pauseSettings(const sf::Event & event, sf::View & view);
		void handleInput();
		void handleEvent(const sf::Event & event, sf::View & view);
		void display(sf::View & view);
};

#endif //__INTERFACE_HPP