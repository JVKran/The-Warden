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
		std::cout << "(!)-- No background specified! World configuration files should always start with a background name." << std::endl;
		worldFile.seekg(0);
	}
	while (!isEmpty(worldFile)){
		try {
			loadTile(worldFile);
		} catch (endOfFile &){
			loadingDone();
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

void World::loadingDone(){
	std::sort(tiles.begin(), tiles.end(), [](const ScreenObject & a, const ScreenObject & b)->bool{
		return a.getPosition().x > b.getPosition().x;
	});
}

void World::draw(const float leftPosition, const float rightPosition, sf::RenderWindow & window){
	background.setPosition((window.getView().getCenter().x-(window.getView().getSize().x*0.5)),0);
	window.draw(background);
	for(ScreenObject & tile : tiles){
		if(tile.getPosition().x + 100 > leftPosition && tile.getPosition().x - 100 < rightPosition){
			tile.draw(window);
			std::cout << tile.getPosition().x << std::endl;
		}
	}
}

void World::setBackground(const std::string & backgroundName){
	background.setTexture(assets.getTexture(backgroundName));
}

bool World::isEmpty(std::ifstream & file){
    return file.peek() == std::ifstream::traits_type::eof();
}

std::vector<ScreenObject> World::getTiles(){
	return(grid.getTiles());
}