/// @file

#ifndef __ASSET_MANAGER
#define __ASSET_MANAGER

#include "../exceptions.hpp"
#include <iostream>
#include "FactoryFunction.hpp"
#include <map>
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>

/// \brief
/// Asset manager
/// \details
/// This class features the storage of all textures of the game. This way, all textures only have to be loaded
/// in memory once after which multiple refrences can be taken of the same texture.
class AssetManager {
	private:
		std::map<std::string, sf::Texture> textureMap;				//!< The map used to retrieve textures based on their name.

		void loadTextures(std::ifstream & input);
	public:
		void loadObjects(const std::string & assetFileName);
		sf::Texture & getTexture(const std::string & assetName);
};

#endif //__ASSET_MANAGER