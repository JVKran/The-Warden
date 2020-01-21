#ifndef __INTERFACE_HPP
#define __INTERFACE_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include <memory>
#include "Game.hpp"
#include "StateMachine.hpp"
#include "InterfaceElement.hpp"
#include "ScreenObject.hpp"

class StateMachine;

class Interface {
	private:
		Game & game;
		Editor & editor;

		sf::RenderWindow & window;

		sf::Sprite background;
		std::vector<InterfaceElement> interfaceElements;
	public:
		Interface(Game & game, StateMachine * machine, Editor & editor, AssetManager & assets, sf::RenderWindow & window);

		void handleInput(StateMachine * machine);
		void handleEvent(const sf::Event & event, StateMachine * machine);
		void display();
};

#endif //__INTERFACE_HPP