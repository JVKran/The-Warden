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
	try {
		while (!isEmpty(worldFile)){
			loadTile(worldFile);
		}
	} catch (endOfFile &){
		std::cout << "Loaded all objects!" << std::endl;
	} catch (std::exception & problem){
		std::cerr << problem.what();
	}
}

void World::loadTile(std::ifstream & input){
	std::string assetName;
	sf::Vector2f position;
	input >> position >> assetName;
	tiles.push_back(ScreenObject(assetName, assets, position));
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
