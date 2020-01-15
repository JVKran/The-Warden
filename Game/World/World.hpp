#ifndef __WORLD_HPP
#define __WORLD_HPP

#include <vector>
#include "ScreenObject.hpp"
#include <string>

class World {
	private:
		AssetManager & assets;
		std::vector<ScreenObject> tiles;

		sf::Sprite background;

		bool isEmpty(std::ifstream & file);
		sf::View & view;
	public:
		World(AssetManager & assets, sf::View & view);

		void loadWorld(const std::string & worldFileName);
		void loadTile(std::ifstream & input);
		void loadingDone();
		sf::View &getView();
		std::vector<ScreenObject> getTiles();

		void draw(const float leftPosition, const float rightPosition, sf::RenderWindow & window);

		void setBackground(const std::string & backgroundName);
};

#endif //__WORLD_HPP