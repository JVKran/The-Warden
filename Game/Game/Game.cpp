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
void Game::handleInput(){
	for(int_fast8_t i = characters.size() - 1; i >= 0; i--){
		// try {
			characters.at(i).update(window, world, characters, bindings);
		// } catch  {

		// }
	}
}

void Game::handleEvent(const sf::Event & event){
	for(int_fast8_t i = characters.size() - 1; i >= 0; i--){
		characters.at(i).handleEvent(event);
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
	std::vector<std::shared_ptr<Item>> startItems;
	startItems.push_back(std::make_shared<Weapon>("club", assets, 10, 500));
	startItems.push_back(std::make_shared<Weapon>("battleAxe", assets, 50, 100));
	startItems.push_back(std::make_shared<Weapon>("bigDagger", assets, 10, 500));
	startItems.push_back(std::make_shared<Weapon>("ironSword", assets, 10, 500));
	
	std::ifstream charactersFile("Characters/instances.txt");
	if(!charactersFile){
		throw fileNotFound("Characters/instances.txt");
	}
	std::string carname="waterBubble";
	std::vector<sf::Vector2i> spritePlayerData;
	std::vector<sf::Vector2i> spritePlayerAction;
	std::vector<std::string> spritePlayerNames;
	//SpriteCharacter characterData(spritePlayerData, spritePlayerAction, spritePlayerNames);
	std::string idleName="";
	std::string idleFile="";
	std::string jumpName="";
	std::string jumpFile="";
	std::string walkName="";
	std::string walkFile="";
	std::string attackName="";
	std::string attackFile="";
	std::string dieName="";
	std::string dieFile="";
	std::string name="";

	
	
	std::string prevstring="";
	sf::Vector2f position;
	std::string filename="";
	while (!isEmpty(charactersFile)){
		//bool data, action, names, textureName;
		
		std::string currstring = "";
				charactersFile>>currstring;
		if((currstring.find("position")!= std::string::npos)){

			charactersFile>>position;
			
			// std::cout<<"rc    "<<position.x<<"     "<<position.y<<'\n';
			// std::cout<<position.x<<'\n';
		}


		if((currstring.find("named")!= std::string::npos)){
			charactersFile>>currstring;
			name=currstring;
			//std::cout<<position.x<<'\n';
		}
		if((currstring.find("idleName")!= std::string::npos)){
			charactersFile>>currstring;
			idleName=currstring;
			//std::cout<<position.x<<'\n';
		}
		if((currstring.find("idleFile")!= std::string::npos)){
			charactersFile>>currstring;
			idleFile=currstring;
			//std::cout<<position.x<<'\n';
		}
		if((currstring.find("jumpName")!= std::string::npos)){
			charactersFile>>currstring;
			jumpName=currstring;
			//std::cout<<position.x<<'\n';
		}if((currstring.find("jumpFile")!= std::string::npos)){
			charactersFile>>currstring;
			jumpFile=currstring;
			//std::cout<<position.x<<'\n';
		}
		if((currstring.find("walkName")!= std::string::npos)){
			charactersFile>>currstring;
			walkName=currstring;
			//std::cout<<position.x<<'\n';
		}
		if((currstring.find("walkFile")!= std::string::npos)){
			charactersFile>>currstring;
			walkFile=currstring;
			//std::cout<<position.x<<'\n';
		}
		
		prevstring=currstring;
		if((currstring.find("eind")!= std::string::npos)){
			SpriteCharacter characterData( idleName, idleFile, jumpName,  jumpFile,  walkName,  walkFile, attackName,  attackFile,  dieName,  dieFile);
			if(name=="player"){
				characters.push_back(Character(position, std::make_shared<PlayerInput>(world, characters), std::make_shared<PhysicsComponent>(), std::make_shared<AnimatedPlayerGraphics>(name, assets, characterData), startItems, world, true));
			}else if (name !=""){
				startItems.at(0) = std::make_shared<Weapon>("club", assets, 10, 500);
				characters.push_back(Character(position, std::make_shared<EnemyInput>(world, characters), std::make_shared<EnemyPhysics>(), std::make_shared<AnimatedPlayerGraphics>(name, assets, characterData), startItems, world));
			}
			 idleName="";
			 idleFile="";
			 jumpName="";
			 jumpFile="";
			 walkName="";
			 walkFile="";
			 attackName="";
			 attackFile="";
			 dieName="";
			 dieFile="";
			 name="";

			currstring="";
			//position={200,350};
			spritePlayerData.clear();
			spritePlayerNames.clear();
			spritePlayerAction.clear();
		}

	}
}