#include "Game.hpp"

Game::Game(const std::string & objectConfigurationFile){
	assets.loadObjects(objectConfigurationFile);				//"Assets/objects.txt"

	window.setVerticalSyncEnabled(1);
	window.setFramerateLimit(60);
}

void Game::handleInput(){
	editor.handleInput(window);
}