/// @file

#include "AssetManager.hpp"

/// \brief
/// Load all objects.
/// \details
/// This loads all objects specified in the file with the name of the passed parameter. 
/// This file should follow some syntax rules:
/// ~~~~~{.txt}
/// background Assets/Textures/freetileset/png/BG/BG.png
/// crate Assets/Textures/freetileset/png/Object/Crate.png
/// grass Assets/Textures/freetileset/png/Tiles/2.png
/// ~~~~~
/// The first word specifies the name that identifies the texture in the textureMap. The second word is equal
/// to the filepath that leads to the desired texture.
/// @param assetFileName The filename of the file containing all assets, their locations and their names.
void AssetManager::loadObjects(const std::string & assetFileName){
	std::ifstream assetFile(assetFileName);
	if(!assetFile){
		throw fileNotFound(assetFileName);
	}
	while (!isEmpty(assetFile)){
		try {
			loadTexture(assetFile);
		} catch (endOfFile &){
		} catch (std::exception & problem){
			std::cerr << problem.what();
		}
	}
}

/// \brief
/// Load one texture.
/// \details
/// This loads one object from the passed ifstream. 
/// This file should follow some syntax rules:
/// ~~~~~{.txt}
/// background Assets/Textures/freetileset/png/BG/BG.png
/// crate Assets/Textures/freetileset/png/Object/Crate.png
/// grass Assets/Textures/freetileset/png/Tiles/2.png
/// ~~~~~
/// The first word specifies the name that identifies the texture in the textureMap. The second word is equal
/// to the filepath that leads to the desired texture.
/// @param input The input to read the textureName and filepath from.
/// \exception noSuchPicture() The filepath provided does not lead to a valid or existing texture.
void AssetManager::loadTexture(std::ifstream & input){
	std::string name, fileName;
	input >> name >> fileName;
	sf::Texture texture;
	if (!texture.loadFromFile(fileName)){
    	throw noSuchPicture(fileName);
	}
	textureMap[name] = texture;
}

/// \brief
/// Get texture.
/// \details
/// This function returns a refrence to the texture identified by the passed
/// texture name.
/// @param assetName The name of the texture to retrieve.
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
