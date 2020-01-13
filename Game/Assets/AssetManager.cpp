#include "AssetManager.hpp"

void AssetManager::loadObjects(const std::string & assetFileName){
	std::ifstream assetFile(assetFileName);
	if(!assetFile){
		throw fileNotFound(assetFileName);
	}
	try {
		while (!is_empty(assetFile)){
			loadTextures();
		}
	} catch (endOfFile &){
		std::cout << "Loaded all objects!" << std::endl;
	} catch (std::exception & problem){
		std::cerr << problem.what();
		return 1;
	}
}

void AssetManager::loadTextures(std::ifstream & input){
	std::string name, fileName;
	input >> name >> fileName;
	sf::Texture texture;
	if (!texture.loadFromFile(fileName)){
    	throw noSuchPicture(fileName);
	}
	textureMap[name] = texture;
}