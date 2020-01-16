#include "AssetManager.hpp"

void AssetManager::loadObjects(const std::string & assetFileName){
	std::ifstream assetFile(assetFileName);
	if(!assetFile){
		throw fileNotFound(assetFileName);
	}
	while (!isEmpty(assetFile)){
		try {
			loadTextures(assetFile);
		} catch (endOfFile &){
		} catch (std::exception & problem){
			std::cerr << problem.what();
		}
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

sf::Texture & AssetManager::getTexture(const std::string & assetName){
	try {
		textureMap.at(assetName);
	} catch (const std::exception & error){
		std::cerr << "(!)-- " << "Texture " << assetName << " not loaded!" << std::endl;
		sf::Texture texture;
		texture.loadFromFile("Assets/Textures/notFound.png");
		textureMap[assetName] = texture;
	}
	return textureMap[assetName];
}

bool AssetManager::isEmpty(std::ifstream & file){
    return file.peek() == std::ifstream::traits_type::eof();
}
