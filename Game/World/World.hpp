#ifndef __WORLD_HPP
#define __WORLD_HPP

#include <vector>
#include "ScreenObject.hpp"
#include <string>
#include "Grid.hpp"

class World {
	private:
		AssetManager & assets;
		Grid grid;
		sf::Sprite background;

		bool isEmpty(std::ifstream & file);
	public:
		World(AssetManager & assets);

		void loadWorld(const std::string & worldFileName);

		void setBackground(const std::string & backgroundName);
		void draw(sf::RenderWindow & window);
};

#endif //__WORLD_HPP