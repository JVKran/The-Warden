/// @file

#include "Game.hpp"

/// \brief
/// Create an instance.
/// \details
/// This creates a Game. After initialization, the AssetManager loads all textures and the Characters are
/// read into memory. Furhtermore, it initializes the world and editor with said AssetManager.
/// @param objectConfigurationFile The file that contains all Textures and their Filepaths.
Game::Game(sf::RenderWindow & window, AssetManager & assets, std::array<KeyBinding, 3> & bindings):
	world(assets),
	window(window),
	bindings(bindings)
{			//"Assets/objects.txt"
	loadCharacters();
	//window.setVerticalSyncEnabled(true);
}

/// \brief
/// Start playing.
/// \details
/// This starts a game by loading the world and changing the state to PLAYING.
void Game::startWorld(const std::string & worldName){
	world.loadWorld(worldName);
}

/// \brief
/// Hanlde input.
/// \details
/// This handles either CharacterInput or EditorInput based on the state of the game.
void Game::handleInput(sf::View & view){
	for(int_fast8_t i = characters.size() - 1; i >= 0; i--){
		characters.at(i).update(window, world, characters, bindings);
	}
}

/// \brief
/// Hanlde Events.
/// \details
/// This handles all the events it gets.
void Game::handleEvent(const sf::Event & event, sf::View & view){
	if( event.type == sf::Event::MouseButtonReleased ){
		if( event.mouseButton.button == sf::Mouse::Right ){
			sf::Vector2f pos = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);
			Tile objectToAdd = {"crate", assets, pos, 1, 1.0, 0.0, 1};
			objectToAdd.setNewScale(1);
			objectToAdd.setFollowMouse(true);
			objectToAdd.setWindowLayer(1);
			world.addTile(objectToAdd);
			objectToAdd.makePartOfWorld(true);
		}
	}
}

/// \brief
/// Display the game.
/// \details
/// This displays the current state of the game on screen.
void Game::display(sf::View & view){
	world.draw(window, view, 0);				// First draw layer 0 of the world.
	world.draw(window, view, 1);				// Then the first layer.
	for(auto & character : characters){
		character.draw(window, view);			// Then all characters.
	}
	for(uint_fast8_t windowLayer = 2; windowLayer <= 4; windowLayer ++){
		world.draw(window, view, windowLayer);				// Finaly, draw one more layer that's also able to draw over Characters.
	}
}


/// \brief
/// Load characters
/// \details
/// This loads all characters in characters.txt. Unfortunately still undergoing changes.
void Game::loadCharacters(){
	characters.push_back(Character(sf::Vector2f(200,350), std::make_shared<EnemyInput>(world, characters), std::make_shared<EnemyPhysics>(), std::make_shared<EnemyGraphics>("bush1", assets), std::make_shared<Weapon>(10, 500), world));
	characters.push_back(Character(sf::Vector2f(600,350), std::make_shared<PlayerInput>(world, characters), std::make_shared<PhysicsComponent>(), std::make_shared<PlayerGraphics>("crate", assets), std::make_shared<Weapon>(15, 100), world, true));
}