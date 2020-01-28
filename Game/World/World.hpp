/// @file

#ifndef __WORLD_HPP
#define __WORLD_HPP

#include <vector>
#include "ScreenObject.hpp"
#include "Exceptions.hpp"
#include "Items.hpp"
#include <string>
#include <memory>

class Item;

/// \brief
/// World
/// \details
/// This class is the entire world. It consists of all the tiles specified in the world configuration file.
/// It's responsible for loading, drawing and saving the world.
class World {
	private:
		AssetManager & assets;						//!< The AssetManager to use for gathering the needed textures.
		std::vector<Tile> tiles;					//!< The tiles the world consists of.
		std::vector<std::shared_ptr<Item>> items;

		std::string worldFileName;					//!< The filename of the world configuration file.
		std::string backgroundName;					//!< The backgroundname used for retrieving the texture from the AssetManager.
		sf::Sprite background;						//!< The background sprite.

		void loadWorld();
		void loadTile(std::ifstream & input);
	public:
		void sortWorld();
		World(AssetManager & assets);

		AssetManager & getAssets(){
			return assets;
		}

		void saveWorld();
		void loadWorld(const std::string & fileName);

		void addTile(Tile object);
		void addItem(std::shared_ptr<Item> item);

		void addTile(std::string object, sf::Vector2f position);
		void setBackground(const std::string & backgroundName);

		std::vector<Tile> & getTiles();
		std::vector<std::shared_ptr<Item>> & getItems(){
			return items;
		}

		void draw(sf::RenderWindow & window, sf::View & view, const int_fast8_t windowLayer);

		World & operator=(World lhs){
			tiles = lhs.tiles;
			worldFileName = lhs.worldFileName;
			backgroundName = lhs.backgroundName;
			background = lhs.background;
			return *this;
		}
};

#endif //__WORLD_HPP