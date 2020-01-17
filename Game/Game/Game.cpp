#include "Game.hpp"

Game::Game(const std::string & objectConfigurationFile):
	world(assets, view),
	editor(assets, view, event),
	speler(sf::Vector2f(500,100),"crate",assets,window)
{
	assets.loadObjects(objectConfigurationFile);				//"Assets/objects.txt"

	//window.setFramerateLimit(60);

	window.setVerticalSyncEnabled(1);
}

void Game::startWorld(const std::string & worldName){
	world.loadWorld(worldName);
	state = states::PLAYING;
}

void Game::editWorld(const std::string & worldName){
	editor.selectWorld(worldName);
	state = states::EDITING;
}

void Game::handleInput(){
	switch(state){
		case states::EDITING: {
			editor.handleInput(window);
			break;
		}
		case states::PLAYING: {
			speler.update(window, world);
			break;
		}
		default: {
			break;
		}
	}
	while(window.pollEvent(event)){
		if( event.type == sf::Event::Closed ){
			window.close();
		}
		switch(state){
			case states::EDITING: {
				editor.handleInput(window);
				break;
			}
			default: {
				break;
			}
		}
	}
}

void Game::display(){
	window.clear();
	switch(state){
		case states::PLAYING: {
			world.draw(window);
			speler.update(window, world);
			break;
		}
		case states::EDITING: {
			editor.draw(window);
			break;
		}
		default: {
			break;
		}
	}
	window.setView(view);
	window.display();
}