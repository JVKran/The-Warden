#include "Game.hpp"
#include "../exceptions.hpp"
#include "FactoryFunction.hpp"

Game::Game(AssetManager & assets, sf::RenderWindow & window):
	assets(assets),
	window(window)
{
	loadCharacters();
}

void Game::loadCharacters(){
	std::ifstream charactersFile("Characters/characters.txt");
	if(!charactersFile){
		throw fileNotFound("Characters/characters.txt");
	}
	while (!isEmpty(charactersFile)){
		bool data, action, names, textureName;
		sf::Vector2i position;
		std::string readName = "";
		std::vector<sf::Vector2i> spritePlayerData;
		std::vector<sf::Vector2i> spritePlayerAction;
		std::vector<std::string> spritePlayerNames;
		try{
			if(data | action){
				charactersFile >> position;
			} else {
				charactersFile >> readName;
			}
		} catch (...){
			if(data){
				action = true;
				data = false;
				std::cout << "Switched to action" << std::endl;
			} else if (action){
				names = true;
				action = false;
				std::cout << "Switched to names" << std::endl;
			}
		}
		if(readName.find("|") != std::string::npos){
			charactersFile >> readName;
			names = false;
			textureName = true;
		}

		std::cout << position.x << ", " << position.y << ", " << readName << std::endl;
		if(data){
			spritePlayerData.push_back(position);
		} else if (action){
			spritePlayerAction.push_back(position);
		} else if (names){
			spritePlayerNames.push_back(readName);
		} else if (textureName){
			//readName contains the textureName.
			data = true;
			textureName = false;
			std::unique_ptr<Character> mainChar = std::make_unique<Character>(sf::Vector2f(500,350), readName, assets, window, spritePlayerData, spritePlayerAction, spritePlayerNames);
			mainChar->draw();
			//characters.push_back();
		}
	}
}

void Game::update(World & world){
	// for(auto & character : characters){
	// 	character.update(window, world, "idle");
	// }
}

bool Game::isEmpty(std::ifstream & file){
    return file.peek() == std::ifstream::traits_type::eof();
}