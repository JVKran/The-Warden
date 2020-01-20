/// @file

#include "Game.hpp"

/// \brief
/// Create an instance.
/// \details
/// This creates a Game. After initialization, the AssetManager loads all textures and the Characters are
/// read into memory. Furhtermore, it initializes the world and editor with said AssetManager.
/// @param objectConfigurationFile The file that contains all Textures and their Filepaths.
Game::Game(const std::string & objectConfigurationFile):
	world(assets),
	editor(assets)
{
	assets.loadObjects(objectConfigurationFile);				//"Assets/objects.txt"
	loadCharacters();
	window.setVerticalSyncEnabled(1);
}

/// \brief
/// Start playing.
/// \details
/// This starts a game by loading the world and changing the state to PLAYING.
void Game::startWorld(const std::string & worldName){
	world.loadWorld(worldName);
	state = states::PLAYING;
}

/// \brief
/// Start editing.
/// \details
/// This starts editing a world by selecing a world to edit and chaning the state to EDITING.
void Game::editWorld(const std::string & worldName){
	editor.selectWorld(worldName);
	state = states::EDITING;
}

/// \brief
/// Hanlde input.
/// \details
/// This handles either CharacterInput or EditorInput based on the state of the game.
void Game::handleInput(){
	switch(state){
		case states::EDITING: {
			editor.handleInput(window, event, view);
			break;
		}
		case states::PLAYING: {
			for(auto & character : characters){
				character.update(window, world, characters);
			}
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
				editor.handleInput(window, event, view);
				break;
			}
			default: {
				break;
			}
		}
	}
}

/// \brief
/// Display the game.
/// \details
/// This displays the current state of the game on screen.
void Game::display(){
	window.clear();
	switch(state){
		case states::PLAYING: {
			world.draw(window, view, 0);				// First draw layer 0 of the world.
			world.draw(window, view, 1);				// Then the first layer.
			for(auto & character : characters){
				character.draw(window, view);			// Then all characters.
			}
			for(uint_fast8_t windowLayer = 2; windowLayer <= 4; windowLayer ++){
				world.draw(window, view, windowLayer);				// Finaly, draw one more layer that's also able to draw over Characters.
			}
			break;
		}
		case states::EDITING: {
			editor.draw(window, view);
			break;
		}
		default: {
			break;
		}
	}
	window.setView(view);
	window.display();
}


/// \brief
/// Load characters
/// \details
/// This loads all characters in characters.txt. Unfortunately still undergoing changes.
void Game::loadCharacters(){
	characters.push_back(Character(sf::Vector2f(200,350), std::make_shared<PlayerInput>(), std::make_shared<PlayerPhysics>(), std::make_shared<PlayerGraphics>("crate", assets), true));
	characters.push_back(Character(sf::Vector2f(200,350), std::make_shared<EnemyInput>(), std::make_shared<PlayerPhysics>(), std::make_shared<EnemyGraphics>("bush1", assets)));
}