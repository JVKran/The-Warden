#ifndef __INTERFACE_HPP
#define __INTERFACE_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include <memory>
#include "Game.hpp"
#include "Settings.hpp"
#include "StateMachine.hpp"

class StateMachine;
class Settings;

class Interface {
	private:
		Game & game;
		Editor & editor;
		Settings & settings;

		sf::RenderWindow & window;

		sf::Sprite background;
		std::vector<sf::Sprite> interfaceElements;
	public:
		Interface(Game & game, Editor & editor, Settings & settings, AssetManager & assets, sf::RenderWindow & window);

		void handleInput(StateMachine * machine);
		void handleEvent(const sf::Event & event, StateMachine * machine);
		void display();
};

#endif //__INTERFACE_HPP