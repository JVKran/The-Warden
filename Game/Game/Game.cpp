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
	bool data,action, names, textureName,go;
		
	std::vector<sf::Vector2i> spritePlayerData;
	std::vector<sf::Vector2i> spritePlayerAction;
	std::vector<std::string> spritePlayerNames;
	while (!isEmpty(charactersFile)){
		
		sf::Vector2i position;
		std::string readName = "";
		try{
			if(data | action){
				charactersFile >> position;
				//std::cout<<position.x<<"\n";
			} else {
				charactersFile >> readName;
				//std::string s = readname;
				//std::cout<<s<"\n";
			}
		} catch (...){
			if(data){
				action = true;
				data = false;
				std::cout << "Switched to action" << std::endl;
				go=false;
			} else if (action){
				names = true;
				action = false;
				std::cout << "Switched to names" << std::endl;
				go=false;
			}
		}
		if(readName.find("|") != std::string::npos){
			charactersFile >> readName;
			names = false;
			textureName = true;
		}
		std::string s =readName;
		//std::cout << position.x << ", " << position.y << ", " << s << std::endl;
		if(go){
			if(data){
				spritePlayerData.push_back(position);
				std::cout << "inD: " <<position.x << ", " << position.y << ", " << s << std::endl;
			} else if (action){

				spritePlayerAction.push_back(position);
				std::cout << "inA: "<<position.x << ", " << position.y << ", " << s << std::endl;
			} else if (names){

				spritePlayerNames.push_back(readName);
				std::cout << "inR: "<<position.x << ", " << position.y << ", " << s << std::endl;
			} else if (textureName){
				data = true;
				textureName = false;
				for(auto&d:spritePlayerData){std::cout<<"Data: "<<d.x <<" : " << d.y <<"\n";}
				for(auto&d:spritePlayerAction){std::cout<<"Action: "<<d.x <<" : " << d.y <<"\n";}
				for(auto&d:spritePlayerNames){std::cout<<"Name: "<<d<<"\n";}
				std::string tmp = readName;
				std::cout << tmp << std::endl;
				characters.push_back(Character(sf::Vector2f(500,350), readName, assets, window, spritePlayerData, spritePlayerAction, spritePlayerNames));
			}
		}else{go=true;}
		
	}
}

void Game::update(World & world){
	for(auto & character : characters){
		character.update(window, world, "idle", true);
	}
}

bool Game::isEmpty(std::ifstream & file){
    return file.peek() == std::ifstream::traits_type::eof();
}