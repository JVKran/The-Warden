#include "World.hpp"
#include "FactoryFunction.hpp"

World::World(AssetManager & assets):
	assets(assets),
	grid(Grid(assets))
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
			grid.loadTile(worldFile);
		} catch (endOfFile &){
			grid.loadingDone();
			break;
		} catch (std::exception & problem){
			std::cerr << problem.what();
			continue;
		}
	}
}

void World::draw(sf::RenderWindow & window){
	background.setPosition((window.getView().getCenter().x-(window.getView().getSize().x*0.5)),0);
	window.draw(background);
	grid.draw(0, 1000, window);
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