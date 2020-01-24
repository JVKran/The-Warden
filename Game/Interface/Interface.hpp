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

class Game;
class StateMachine;
class Settings;

class Interface {
	private:
		Game & game;
		Editor & editor;
		AssetManager & assets;
		Settings & settings;

		World world;

		sf::RenderWindow & window;

		bool pauseGame=false;

		sf::Sprite background;
		std::vector<InterfaceElement> interfaceElements;
		std::vector<InterfaceElement> pauseElements;
		sf::RectangleShape pauseBackground;
	public:
		Interface(Game & game, Editor & editor, Settings & settings, AssetManager & assets, sf::RenderWindow & window);

		void initialize(StateMachine * machine);
		void goToPauseMenu();
		void pauseSettings(const sf::Event & event, sf::View & view);
		void handleInput();
		void handleEvent(const sf::Event & event, sf::View & view);
		void display(sf::View & view);
};

#endif //__INTERFACE_HPP