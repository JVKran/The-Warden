#ifndef __ASSET_MANAGER
#define __ASSET_MANAGER

#include <map>
#include <string>
#include <fstream>

class AssetManager {
	private:
		std::map<std::string, sf::Texture> textureMap;
	public:
		void loadObjects(const std::string & assetFileName);
};

#endif //__ASSET_MANAGER