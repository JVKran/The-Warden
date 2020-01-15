#include "World.hpp"
#include "FactoryFunction.hpp"
#include "Editor.hpp"

World::World(AssetManager & assets, const std::string & worldFileName):
	assets(assets),
	worldFileName(worldFileName)
{
	loadWorld();
}

void World::loadWorld(){
	std::ifstream worldFile(worldFileName);
	if(!worldFile){
		throw fileNotFound(worldFileName);
	}
	worldFile >> backgroundName;
	setBackground(backgroundName);
	if ((backgroundName.find("(") != std::string::npos)){
		std::cout << "(!)-- No background specified! World configuration files should always start with a background name." << std::endl;
		worldFile.seekg(0);
	}
	while (!isEmpty(worldFile)){
		try {
			loadTile(worldFile);
		} catch (std::exception & problem){
			std::cerr << problem.what();
			continue;
		}
	}
	loadingDone();
}

void World::loadTile(std::ifstream & input){
	std::string assetName;
	sf::Vector2f position;
	float scale;
	input >> position >> assetName >> scale;
	tiles.push_back(SelectableObject(assetName, assets, position, scale));
}

void World::loadingDone(){
	std::sort(tiles.begin(), tiles.end(), [](const SelectableObject & a, const SelectableObject & b)->bool{
		return a.getPosition().x > b.getPosition().x;
	});
}

void World::draw(const float leftPosition, const float rightPosition, sf::RenderWindow & window){
	background.setPosition((window.getView().getCenter().x-(window.getView().getSize().x*0.5)),0);
	window.draw(background);
	for(SelectableObject & tile : tiles){
		if(tile.getPosition().x + 100 > leftPosition && tile.getPosition().x - 100 < rightPosition){
			tile.draw(window);
		}
	}
}

void World::addTile(SelectableObject & object){
	tiles.push_back(object);
}

std::vector<SelectableObject> & World::getTiles(){
	return tiles;
}

void World::saveWorld(){
	loadingDone();
	std::ofstream worldFile (worldFileName, std::ofstream::out);
	std::cout << "(!)-- Saving world to " << worldFileName << std::endl;

	worldFile << backgroundName << std::endl;
	for(const SelectableObject & tile : tiles ){
		worldFile << tile.getConfiguration() << std::endl;
		std::cout << tile.getConfiguration() << std::endl;
	}

	worldFile.close();
}

void World::setBackground(const std::string & backgroundName){
	background.setTexture(assets.getTexture(backgroundName));
}

bool World::isEmpty(std::ifstream & file){
    return file.peek() == std::ifstream::traits_type::eof();
}
