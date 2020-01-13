#ifndef __ASSET_MANAGER
#define __ASSET_MANAGER

#include <map>
#include <string>
#include <fstream>
#include "exceptions.hpp"

class AssetManager {
	private:
		std::map<std::string, sf::Texture> textureMap;

		void loadTextures(std::ifstream & input);
	public:
		void loadObjects(const std::string & assetFileName);
};

#endif //__ASSET_MANAGER