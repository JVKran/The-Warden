#ifndef __ASSET_MANAGER
#define __ASSET_MANAGER

#include "../exceptions.hpp"
#include <iostream>
#include <map>
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>

class AssetManager {
	private:
		std::map<std::string, sf::Texture> textureMap;

		void loadTextures(std::ifstream & input);
		bool isEmpty(std::ifstream & file);
	public:
		void loadObjects(const std::string & assetFileName);
		sf::Texture & getTexture(const std::string & assetName);
};

#endif //__ASSET_MANAGER