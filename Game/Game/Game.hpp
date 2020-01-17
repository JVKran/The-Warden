#ifndef __GAME_HPP
#define __GAME_HPP

#include "Character.hpp"
#include "AssetManager.hpp"
#include "World.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class Game {
	private:
		AssetManager & assets;
		sf::RenderWindow & window;

		std::vector<Character> characters;

		void loadCharacters();
		bool isEmpty(std::ifstream & file);
	public:
		Game(AssetManager & assets, sf::RenderWindow & window);

		void update(World & world);

};


#endif //__GAME_HPP