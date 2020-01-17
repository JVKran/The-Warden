#ifndef __GAME_HPP
#define __GAME_HPP

#include "Character.hpp"
#include "AssetManager.hpp"
#include "World.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

class Game {
	private:
		AssetManager & assets;
		sf::RenderWindow & window;

		void loadCharacters();
		bool isEmpty(std::ifstream & file);
	public:
		Game(AssetManager & assets, sf::RenderWindow & window);

		void update(World & world);

};


#endif //__GAME_HPP