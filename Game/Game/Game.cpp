#include "Game.hpp"

Game::Game(const std::string & objectConfigurationFile):
	world(assets, view),
	editor(assets, view, event)
{
	assets.loadObjects(objectConfigurationFile);				//"Assets/objects.txt"
	loadCharacters();
	//characters.push_back(Character(sf::Vector2f(500,100),"player",assets,window, std::make_shared<PlayerInput>(), std::make_shared<PlayerPhysics>(), std::make_shared<PlayerGraphics>("player", assets)));

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
			for(auto & character : characters){
				character.update(window, world);
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
			for(auto & character : characters){
				character.update(window, world);
			}
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


void Game::loadCharacters(){
	std::ifstream charactersFile("Characters/characters.txt");
	if(!charactersFile){
		throw fileNotFound("Characters/characters.txt");
	}
	std::vector<sf::Vector2i> spritePlayerData;
	std::vector<sf::Vector2i> spritePlayerAction;
	std::vector<std::string> spritePlayerNames;
	spriteCharacter characterData(spritePlayerData, spritePlayerAction, spritePlayerNames);
	while (!isEmpty(charactersFile)){
		bool data, action, names, textureName;
		sf::Vector2i position;
		std::string readName = "";
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
			} else if (action){
				names = true;
				action = false;
			}
		}
		if(readName.find("|") != std::string::npos){
			charactersFile >> readName;
			names = false;
			textureName = true;
		}

		//std::cout << position.x << ", " << position.y << ", " << readName << std::endl;
		if(data){
			spritePlayerData.push_back(position);
		} else if (action){
			spritePlayerAction.push_back(position);
		} else if (names){
			spritePlayerNames.push_back(readName);
		} else if (textureName){
			//readName contains the textureName.
			// spritePlayerData = {sf::Vector2i{350,592},sf::Vector2i{7,16}, sf::Vector2i{5,5}, sf::Vector2i{3,0}};
			spritePlayerAction.erase(spritePlayerAction.begin());
			spritePlayerNames.erase(spritePlayerNames.begin());
			for(const auto & vector : spritePlayerData){
				std::cout << '(' << vector.x << ',' << vector.y << ')' << std::endl;
			}
			for(const auto & vector : spritePlayerAction){
				std::cout << '(' << vector.x << ',' << vector.y << ')' << std::endl;
			}
			for(const auto & vector : spritePlayerNames){
				std::cout << vector << std::endl;
			}
			std::cout << readName << std::endl;
			// spritePlayerAction = { sf::Vector2i{0,0}, sf::Vector2i{3,0}, sf::Vector2i{3,3}, sf::Vector2i{0,0}, sf::Vector2i{1,1},sf::Vector2i{0,0}, sf::Vector2i{2,2}, sf::Vector2i{6,1}};
			// spritePlayerNames = {"idle","slide", "walk", "jump"};
			characterData = spriteCharacter(spritePlayerData, spritePlayerAction, spritePlayerNames);
			data = true;
			textureName = false;
			if(readName == "player"){
				characters.push_back(Character(sf::Vector2f(500,350), window, std::make_shared<PlayerInput>(), std::make_shared<PlayerPhysics>(), std::make_shared<PlayerGraphics>(readName, assets, characterData)));
			} 
			//if(readName != "player"){
			//	type = ArtificalInput() oid.
			//}
		}
	}
}