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
		Game & game;
		Editor & editor;
		AssetManager & assets;
		Settings & settings;
		StateMachine * machine;
		World world;

		sf::RenderWindow & window;

		bool pauseGame=false;

		sf::Sprite background;

		std::vector<InterfaceElement> interfaceElements;
		std::vector<InterfaceElement> pauseElements;

		sf::RectangleShape pauseBackground;
		std::shared_ptr<State> prevState;
	public:
		Interface(Game & game, Editor & editor, Settings & settings, AssetManager & assets, sf::RenderWindow & window);

		void initialize(StateMachine * newMachine);
		void pauseSettings(const sf::Event & event, sf::View & view);
		void handleInput();
		void handleEvent(const sf::Event & event, sf::View & view);
		void display(sf::View & view);
};

#endif //__INTERFACE_HPP