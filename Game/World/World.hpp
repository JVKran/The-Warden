/// @file

#ifndef __WORLD_HPP
#define __WORLD_HPP

#include <vector>
#include "ScreenObject.hpp"
#include "../exceptions.hpp"
#include <string>

/// \brief
/// World
/// \details
/// This class is the entire world. It consists of all the tiles specified in the world configuration file.
/// It's responsible for loading, drawing and saving the world.
class World {
	private:
		AssetManager & assets;
		std::vector<SelectableObject> tiles;

		const std::string worldFileName;
		std::string backgroundName;
		sf::Sprite background;

		sf::View & view;

		bool isEmpty(std::ifstream & file);

		void loadWorld();
		void loadTile(std::ifstream & input);
		void loadingDone();
	public:
		World(AssetManager & assets, const std::string & worldFileName, sf::View & view);

		void saveWorld();
		void addTile(SelectableObject object);
		void setBackground(const std::string & backgroundName);

		sf::View &getView();
		std::vector<SelectableObject> & getTiles();

		void draw(sf::RenderWindow & window);
};

#endif //__WORLD_HPP