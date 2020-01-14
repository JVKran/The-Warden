#ifndef __WORLD_HPP
#define __WORLD_HPP

#include <vector>
#include "ScreenObject.hpp"

class World {
	private:
		AssetManager & assets;
		std::vector<ScreenObject> tiles;
		sf::Sprite background;

		void loadTile(std::ifstream & input);
		bool isEmpty(std::ifstream & file);
	public:
		World(AssetManager & assets);

		void loadWorld(const std::string & worldFileName);

		void setBackground(const std::string & backgroundName);
		void draw(sf::RenderWindow & window);
		bool collision(sf::FloatRect subject);
		std::vector<ScreenObject> getTiles();
};

#endif //__WORLD_HPP