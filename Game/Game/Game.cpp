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
	//characters.push_back(Character(sf::Vector2f(500,100),"player",assets,window, std::make_shared<PlayerInput>(), std::make_shared<PlayerPhysics>(), std::make_shared<PlayerGraphics>("player", assets)));

	//window.setFramerateLimit(60);

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
	
	std::ifstream charactersFile("Characters/instances.txt");
	if(!charactersFile){
		throw fileNotFound("Characters/instances.txt");
	}
	std::string carname="player";
	std::vector<sf::Vector2i> spritePlayerData;
	std::vector<sf::Vector2i> spritePlayerAction;
	std::vector<std::string> spritePlayerNames;
	SpriteCharacter characterData(spritePlayerData, spritePlayerAction, spritePlayerNames);
	std::string prevstring="";
	sf::Vector2i position;
	std::string filename="";
	while (!isEmpty(charactersFile)){
		//bool data, action, names, textureName;
		
		std::string currstring = "";


		charactersFile>>currstring;
		/*
		//std::cout<<readName<<'\n';
		if((currstring.find("size")!= std::string::npos)){
			charactersFile>>position;
			spritePlayerData.push_back(position);
			
			//std::cout<<position.x<<'\n';
		}

		if((currstring.find("grid")!= std::string::npos)){
			charactersFile>>position;
			spritePlayerData.push_back(position);
			//std::cout<<position.x<<'\n';
		}
		if((currstring.find("action")!= std::string::npos)){
			charactersFile>>position;
			spritePlayerAction.push_back(position);
			//std::cout<<position.x<<'\n';
		}
		if((currstring.find("scale")!= std::string::npos)){
			charactersFile>>position;
			spritePlayerData.push_back(position);
			
			//std::cout<<position.x<<'\n';
		}
		
		if((currstring.find("state")!= std::string::npos)){
			charactersFile>>currstring;
			spritePlayerNames.push_back(currstring);
			//std::cout<<position.x<<'\n';
		}
		if((currstring.find("filename")!= std::string::npos)){
			charactersFile>>currstring;
			filename=currstring;
			//std::cout<<position.x<<'\n';
		}
		*/
		prevstring=currstring;
		//characterData = SpriteCharacter(spritePlayerData, spritePlayerAction, spritePlayerNames);
		if(currstring == carname){
				//std::cout<<spritePlayerData[2].x<<"   "<<spritePlayerData[0].y<<'\n';				std::cout<<"jawoel"<<'\n';
		 		characters.push_back(Character(sf::Vector2f(500,350), std::make_shared<PlayerInput>(), std::make_shared<PlayerPhysics>(), std::make_shared<PlayerGraphics>(currstring, assets, characterData)));
		 		std::cout<<"jawoeplayerl"<<'\n';
			 } 
		if((currstring.find("eind")!= std::string::npos)){
			currstring="";
			spritePlayerData.clear();
			spritePlayerNames.clear();
			spritePlayerAction.clear();
			std::cout<<"CLEAAAAARED"<<'\n';
			//std::cout<<position.x<<'\n';
		}

	

		// try{
		// 	if(data | action){
		// 		charactersFile >> position;
		// 	} else {
		// 		charactersFile >> readName;
		// 	}
		// } catch (...){
		// 	//std::cout<<"caught"<<'\n';
		// 	if(data){
		// 		action = true;
		// 		data = false;
		// 	} else if (action){
		// 		names = true;
		// 		action = false;
		// 	}
		// }
		// if(readName.find("|") != std::string::npos&&0){
		// 	charactersFile >> readName;
		// 	names = false;
		// 	textureName = true;

		// }		if(readName.find("/") != std::string::npos&&0){
		// 	std::string testvar;
		// 	charactersFile >> testvar;
		// 	std::cout<<testvar<<'\n';
		// 	//names = false;
		// 	//textureName = true;

		// }
		// //std::cout<<readName<<'\n';
		// //std::cout << position.x << ", " << position.y << ", " << readName << std::endl;
		// if(data){
		// 	spritePlayerData.push_back(position);
		// 	//std::cout<<position.x<<'\n';
		// } else if (action){
		// 	spritePlayerAction.push_back(position);
		// } else if (names){
		// 	//std::cout<<"names   "<<readName<<'\n';
		// 	spritePlayerNames.push_back(readName);
		// } else if (textureName){
		// 	//readName contains the textureName.
		// 	// spritePlayerData = {sf::Vector2i{350,592},sf::Vector2i{7,16}, sf::Vector2i{5,5}, sf::Vector2i{3,0}};
		// 	spritePlayerAction.erase(spritePlayerAction.begin());
		// 	spritePlayerNames.erase(spritePlayerNames.begin());
		// 	// for(const auto & vector : spritePlayerData){
		// 	// 	std::cout << '(' << vector.x << ',' << vector.y << ')' << std::endl;
		// 	// }
		// 	// for(const auto & vector : spritePlayerAction){
		// 	// 	std::cout << '(' << vector.x << ',' << vector.y << ')' << std::endl;
		// 	// }
		// 	// for(const auto & vector : spritePlayerNames){
		// 	// 	std::cout << vector << std::endl;
		// 	// }
		// 	// std::cout << readName << std::endl;
		// 	// spritePlayerAction = { sf::Vector2i{0,0}, sf::Vector2i{3,0}, sf::Vector2i{3,3}, sf::Vector2i{0,0}, sf::Vector2i{1,1},sf::Vector2i{0,0}, sf::Vector2i{2,2}, sf::Vector2i{6,1}};
		// 	// spritePlayerNames = {"idle","slide", "walk", "jump"};
		// 	characterData = SpriteCharacter(spritePlayerData, spritePlayerAction, spritePlayerNames);
		// 	//std::cout<<spritePlayerNames[0]<<'\n';
		// 	data = true;
		// 	textureName = false;
		// 	if(readName == "waterBubble"){
		// 		characters.push_back(Character(sf::Vector2f(500,350), std::make_shared<PlayerInput>(), std::make_shared<PlayerPhysics>(), std::make_shared<PlayerGraphics>(readName, assets, characterData)));
		// 	} else
		// 	{
		// 		spritePlayerNames.clear();
		// 		spritePlayerData.clear();
		// 		spritePlayerAction.clear();
		// 	}
			
		// 	//if(readName != "player"){
		// 	//	type = ArtificalInput() oid.
		// 	//}
		// }
	}
}