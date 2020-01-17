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

		std::vector<sf::Vector2i> spritePlayerData{sf::Vector2i{350,592},sf::Vector2i{7,16}, sf::Vector2i{5,5}, sf::Vector2i{3,0}};
		std::vector<sf::Vector2i> spritePlayerAction{ sf::Vector2i{0,0}, sf::Vector2i{3,0}, sf::Vector2i{3,3}, sf::Vector2i{0,0}, sf::Vector2i{1,1},sf::Vector2i{0,0}, sf::Vector2i{2,2}, sf::Vector2i{6,1}};
		std::vector<std::string> spritePlayerNames{"idle","slide", "walk", "jump"};

		AssetManager & assets;
		sf::RenderWindow & window;

		Character character;

		// void loadCharacters();
		bool isEmpty(std::ifstream & file);
	public:
		Game(AssetManager & assets, sf::RenderWindow & window);

		void update(World & world);

};


#endif //__GAME_HPP