#ifndef __INTERFACE_HPP
#define __INTERFACE_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include "Game.hpp"

class Interface {
	private:
		Game & game;
		sf::RenderWindow & window;

		sf::Sprite background;
		std::vector<sf::Sprite> interfaceElements;

		enum class states {IDLE, DISPLAYING};
		states state = states::DISPLAYING;
	public:
		Interface(Game & game, AssetManager & assets, sf::RenderWindow & window);

		void handleInput(const sf::Event & event);
		void display();
};

#endif //__INTERFACE_HPP