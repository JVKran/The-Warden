#include "Game.hpp"

Game::Game(const std::string & objectConfigurationFile, const std::vector<std::string> & worldFileNames){
	assets.loadObjects(objectConfigurationFile);				//"Assets/objects.txt"

	worldConfigurationFiles = worldFileNames;
	window.setVerticalSyncEnabled(1);
	window.setFramerateLimit(60);

	world = World(assets, "World/world.txt", view);
}

void Game::handleInput(){
	editor.handleInput(window);
}

void Game::startWorld(const std::string & worldName){
	world = World(assets, "World/" + worldName, view);
}

void Game::draw(){
	window.clear();
	world.draw(window);
	window.display();
}