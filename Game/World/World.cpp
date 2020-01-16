#include "World.hpp"
#include "FactoryFunction.hpp"
#include "Editor.hpp"

World::World(AssetManager & assets, const std::string & worldFileName, sf::View & view):
	assets(assets),
	worldFileName(worldFileName),
	view(view)
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
		} catch(std::ifstream::failure & e){
			std::cerr << "(!)-- Exception opening, reading or closing file\n";
		} catch (const std::exception & problem){
			std::cerr << "(!)-- " << problem.what() << " in file " << __FILE__ << " at line " << __LINE__ << "." << std::endl;
			//continue;
		} catch (...){
			std::cerr << "(!)-- Something went wrong in " << __FILE__ << " at line " << std::to_string(__LINE__) << std::endl;
		}
	}
	loadingDone();
}

void World::loadTile(std::ifstream & input){
	std::string assetName;
	sf::Vector2f position;
	float scale;
	bool collidable;
	input >> position >> assetName >> collidable >> scale;
	tiles.push_back(SelectableObject(assetName, assets, position, scale, collidable));
}

void World::loadingDone(){
	std::cout << "(i)-- Loading world done." << std::endl;

	// try {
	// 	if(!std::is_sorted(tiles.begin(), tiles.end())){
	// 		std::sort(tiles.begin(), tiles.end(), [](const SelectableObject & a, const SelectableObject & b)->bool{
	// 			return a.getPosition().x > b.getPosition().x;
	// 		});
	// 	}
	// } catch (...){
	// 	throw sortingFailed(__FILE__, __LINE__);
	// }
}

void World::draw(sf::RenderWindow & window){
	background.setPosition((window.getView().getCenter().x-(window.getView().getSize().x*0.5)),0);
	window.draw(background);
	for(SelectableObject & tile : tiles){
		if(tile.getPosition().x + 100 > view.getCenter().x-view.getSize().x && tile.getPosition().x - 100 < view.getCenter().x+view.getSize().x){
			tile.draw(window);
			//std::cout << tile.getPosition().x << std::endl;
		}
	}
}

void World::addTile(SelectableObject object){
	tiles.push_back(object);
}

std::vector<SelectableObject> & World::getTiles(){
	return tiles;
}

void World::saveWorld(){
	try {
		loadingDone();
		std::ofstream worldFile (worldFileName, std::ofstream::out);
		std::cout << "(i)-- Saving world to " << worldFileName << std::endl;

		worldFile << backgroundName << std::endl;
		for(const SelectableObject & tile : tiles ){
			worldFile << tile.getConfiguration() << std::endl;
		}

		worldFile.close();
	} catch(const sortingFailed & error){
		std::cerr << error.what();
	} catch (const std::exception & error){
		std::cerr << "(!)-- " << error.what() << std::endl;
	} catch (...){
		std::cerr << "(!)-- Something went wrong..." << std::endl;
	}
	std::cout << "(i)-- Saving world succesful!" << std::endl;
}

void World::setBackground(const std::string & backgroundName){
	background.setTexture(assets.getTexture(backgroundName));
}

bool World::isEmpty(std::ifstream & file){
    return file.peek() == std::ifstream::traits_type::eof();
}

sf::View &World::getView(){
	return(view);
}