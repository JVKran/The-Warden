#include "AssetManager.hpp"

void AssetManager::loadObjects(const std::string & assetFileName){
	std::ifstream assetFile(assetFileName);
	if(!assetFile){
		throw fileNotFound(assetFileName);
	}
	try {
		while (!isEmpty(assetFile)){
			loadTextures(assetFile);
		}
	} catch (endOfFile &){
		std::cout << "Loaded all objects!" << std::endl;
	} catch (std::exception & problem){
		std::cerr << problem.what();
	}
}

void AssetManager::loadTextures(std::ifstream & input){
	std::string name, fileName;
	input >> name >> fileName;
	std::cout << "File " << fileName << " found!" << std::endl;
	sf::Texture texture;
	if (!texture.loadFromFile(fileName)){
    	throw noSuchPicture(fileName);
	}
	textureMap[name] = texture;
}

sf::Texture & AssetManager::getTexture(const std::string & assetName){
	return textureMap.at(assetName);
}

bool AssetManager::isEmpty(std::ifstream & file){
    return file.peek() == std::ifstream::traits_type::eof();
}
