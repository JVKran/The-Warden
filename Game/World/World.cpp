#include "World.hpp"
#include "FactoryFunction.hpp"

World::World(AssetManager & assets):
	assets(assets)
{}

void World::loadWorld(const std::string & worldFileName){
	std::ifstream worldFile(worldFileName);
	if(!worldFile){
		throw fileNotFound(worldFileName);
	}
	std::string worldName;
	worldFile >> worldName;
	setBackground(worldName);
	if ((worldName.find("(") != std::string::npos)){
		//Not triggered
		std::cout << "(!)-- No background specified! World configuration files should always start with a background name." << std::endl;
		worldFile.seekg(0);
	}
	while (!isEmpty(worldFile)){
		try {
			loadTile(worldFile);
		} catch (endOfFile &){
			//Sort Vector
			break;
		} catch (std::exception & problem){
			std::cerr << problem.what();
			continue;
		}
	}
}

void World::loadTile(std::ifstream & input){
	std::string assetName;
	sf::Vector2f position;
	float scale;
	input >> position >> assetName >> scale;
	tiles.push_back(ScreenObject(assetName, assets, position, scale));
}

void World::draw(sf::RenderWindow & window){
	window.draw(background);
	for(auto & tile : tiles){
		tile.draw(window);
	}
}

void World::setBackground(const std::string & backgroundName){
	background.setTexture(assets.getTexture(backgroundName));
}

bool World::isEmpty(std::ifstream & file){
    return file.peek() == std::ifstream::traits_type::eof();
}
