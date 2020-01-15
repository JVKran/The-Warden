#ifndef __WORLD_HPP
#define __WORLD_HPP

#include <vector>
#include "ScreenObject.hpp"
#include <string>

class World {
	private:
		AssetManager & assets;
		std::vector<ScreenObject> tiles;

		const std::string worldFileName;
		sf::Sprite background;

		bool isEmpty(std::ifstream & file);

		void loadWorld();
		void loadTile(std::ifstream & input);
		void loadingDone();
	public:
		World(AssetManager & assets, const std::string & worldFileName);
		~World(){
			saveWorld();
		}

		void saveWorld();

		void draw(const float leftPosition, const float rightPosition, sf::RenderWindow & window);

		void setBackground(const std::string & backgroundName);
};

#endif //__WORLD_HPP