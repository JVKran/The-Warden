#ifndef __INTERFACE_HPP
#define __INTERFACE_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include <memory>
#include "Game.hpp"
#include "StateMachine.hpp"

class StateMachine;

class Interface {
	private:
		Game & game;
		Editor & editor;

		sf::RenderWindow & window;

		sf::Sprite background;
		std::vector<sf::Sprite> interfaceElements;
	public:
		Interface(Game & game, Editor & editor, AssetManager & assets, sf::RenderWindow & window);

		void handleInput(const sf::Event & event, StateMachine * machine);
		void display();
};

#endif //__INTERFACE_HPP