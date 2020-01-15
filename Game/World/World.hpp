#ifndef __WORLD_HPP
#define __WORLD_HPP

#include <vector>
#include "ScreenObject.hpp"
#include "../exceptions.hpp"
#include <string>

class SelectableObject;

class World {
	private:
		AssetManager & assets;
		std::vector<SelectableObject> tiles;

		const std::string worldFileName;
		std::string backgroundName;
		sf::Sprite background;

		bool isEmpty(std::ifstream & file);

		void loadWorld();
		void loadTile(std::ifstream & input);
		void loadingDone();
	public:
		World(AssetManager & assets, const std::string & worldFileName);

		void saveWorld();

		void draw(const float leftPosition, const float rightPosition, sf::RenderWindow & window);

		std::vector<SelectableObject> & getTiles();
		void setBackground(const std::string & backgroundName);
		void addTile(SelectableObject object);
};

#endif //__WORLD_HPP