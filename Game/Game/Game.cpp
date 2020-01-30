/// @file

#include "Game.hpp"

/// \brief
/// Create an instance.
/// \details
/// This creates a Game. After initialization, all characters are loaded into memory. In the background, 
/// also the world is loaded and initialized. Furthermore, all fonts are set and sprites are loaded.
/// @param window The sf::RenderWindow literally everything is drawn into.
/// @param assets The AssetManager that's used to retrieve loaded textures.
/// @param bindings The KeyBindings to use throughout the entire game.
/// @param event The sf::Event to use for detecting and handling occured events.
/// @param view The sf::View to determine the position of for making sure only the minimal is drawn.
Game::Game(sf::RenderWindow & window, AssetManager & assets, std::vector<KeyBinding> & bindings, const sf::Event & event, sf::View & view):
	world(assets),
	window(window),
	bindings(bindings),
	event(event),
	view(view)
{
	loadCharacters();
	keyInput = std::make_shared<PlayerInput>(world, characters);
	visionInput = std::make_shared<InteractiveInput>(world, characters);
	if (!font.loadFromFile("Minecraft.ttf")){
	    std::cerr << "(!)-- Font Minecraft.ttf not found" << std::endl;
	} else {
		scoreText.setFont(font);
		experienceText.setFont(font);
		saveText.setFont(font);
		highScoreText.setFont(font);
	}
	timeSprite.setTexture(assets.getTexture("time"));
	experienceSprite.setTexture(assets.getTexture("experience"));
	savePointSprite.setTexture(assets.getTexture("checkpoint"));
	highScoreSprite.setTexture(assets.getTexture("starLogo"));
	highScoreSprite.setScale(0.12, 0.12);

	scoreText.setFillColor(sf::Color::Black);
	experienceText.setFillColor(sf::Color::Black);
	saveText.setFillColor(sf::Color::Black);
	highScoreText.setFillColor(sf::Color::Black);
}

/// \brief
/// Destruct an instance.
/// \details
/// This closes the sf::RenderWindow when the game gets destructed.
Game::~Game(){
	window.close();
}

/// \brief
/// Start playing.
/// \details
/// This starts a game by loading the world
void Game::startWorld(const std::string & worldName){
	world.loadWorld(worldName);
}

/// \brief
/// Restart clocks
/// \details
/// This restarts the clocks of all characters to make sure every player has their maximum amount of seconds on the clock and
/// sprite animations start from the beginning.
/// This will also pause the game timer.
void Game::restartClocks(){
	for(int_fast8_t i = characters.size() - 1; i >= 0; i--){
		characters.at(i).restartClock();
	}
	clock.restart();
	lastTime = 0.0;
};

/// \brief
/// Restart the entire game.
/// \details
/// This restarts the entire game; the characters, world, clocks, progress
void Game::restart(){
	loadCharacters();
	clock.restart();
	currentSavePoint = 0;
	characters.clear();
	loadCharacters();
	world.getTiles().clear();
	world.getItems().clear();
	startWorld("World/world.txt");
	remainingGameTime = 600;
	lastTime = 0;
}

/// \brief
/// Handle input.
/// \details
/// This handles the input for all characters, manages the time and takes care of savepoints.
/// @param view The sf::View.
/// @param event The sf::Event to use for detecting and handling occured events.
void Game::handleInput(sf::View & view, const sf::Event & event){
	for(int_fast8_t i = characters.size() - 1; i >= 0; i--){
		if(!characters.at(i).isPlayer()){
			characters.at(i).handleEvent(event);
		}
	}
	for(int_fast8_t i = characters.size() - 1; i >= 0; i--){
		characters.at(i).update(window, world, characters, bindings);
	}
	if(clock.getElapsedTime().asMilliseconds() - lastTime >= 900){
		remainingGameTime -= (clock.getElapsedTime().asMilliseconds() - lastTime) / 1000;
		lastTime = clock.getElapsedTime().asMilliseconds();
	}
	for(Character & character : characters){
		if(character.isPlayer()){
			try{
				if(character.getPosition().x > savePoints.at(currentSavePoint)){
					character.setSpawn(character.getPosition());
					std::cout << "(i)-- Reached savepoint " << ++currentSavePoint << "!" << std::endl;
				}
			} catch(std::exception & error){
				std::cout << "(i)-- End of game reached at position " << character.getPosition().x << "!" << std::endl;
				scores.push_back(character.getExperience() + remainingGameTime);
				restart();
			}
			if(sf::Keyboard::isKeyPressed(bindings[15].getKey())){
				character.setInput(visionInput);
			}
			if(sf::Keyboard::isKeyPressed(bindings[16].getKey())){
				character.setInput(keyInput);
			}
		}
	}
}
/// \brief
/// Handle Events.
/// \details
/// This handles all character handleable occured events.
void Game::handleEvent(const sf::Event & event, sf::View & view){
	for(int_fast8_t i = characters.size() - 1; i >= 0; i--){
		characters.at(i).handleEvent(event);
	}
}

/// \brief
/// Display the game.
/// \details
/// This displays the current state of the game on screen; the characters, world, healthbar, items, scores and savepoints.
void Game::display(sf::View & view){
	world.draw(window, view, 0);									// First draw layer 0 of the world.
	world.draw(window, view, 1);									// Then the first layer.

	for(int_fast8_t i = characters.size() - 1; i >= 0; i--){
		characters[i].draw(window, view);							// Then all characters.
	}

	for(uint_fast8_t windowLayer = 2; windowLayer <= 4; windowLayer ++){
		world.draw(window, view, windowLayer);						// Finaly, draw several more layers that are also able to draw over Characters.
	}

	for(const Character & character : characters){
		if(character.isPlayer()){
			experienceText.setString(std::to_string(character.getExperience()));
		}
	}

	scoreText.setString(std::to_string(remainingGameTime));
	scoreText.setPosition(view.getCenter() - sf::Vector2f(view.getSize().x / 2 - 40, view.getSize().y / 2));
	window.draw(scoreText);
	timeSprite.setPosition(view.getCenter() - sf::Vector2f(view.getSize().x / 2 - 5, view.getSize().y / 2 - 3));
	window.draw(timeSprite);

	experienceText.setPosition(view.getCenter() - sf::Vector2f(view.getSize().x / 2 - 40, view.getSize().y / 2 - 30));
	window.draw(experienceText);
	experienceSprite.setPosition(view.getCenter() - sf::Vector2f(view.getSize().x / 2 - 5, view.getSize().y / 2 - 33));
	window.draw(experienceSprite);

	saveText.setString(std::to_string(currentSavePoint));
	saveText.setPosition(view.getCenter() - sf::Vector2f(view.getSize().x / 2 - 40, view.getSize().y / 2 - 60));
	window.draw(saveText);
	savePointSprite.setPosition(view.getCenter() - sf::Vector2f(view.getSize().x / 2 - 5, view.getSize().y / 2 - 63));
	window.draw(savePointSprite);

	highScoreText.setString(std::to_string(*std::max_element(scores.begin(), scores.end())));
	highScoreText.setPosition(view.getCenter() - sf::Vector2f(view.getSize().x / 2 - 40, view.getSize().y / 2 - 90));
	window.draw(highScoreText);
	highScoreSprite.setPosition(view.getCenter() - sf::Vector2f(view.getSize().x / 2 - 5, view.getSize().y / 2 - 93));
	window.draw(highScoreSprite);
}


/// \brief
/// Load characters
/// \details
/// This loads all characters in characters.txt, gives them some items, reads in the textures and writes them
/// into the vector with Characters.
void Game::loadCharacters(){
	std::vector<std::shared_ptr<Item>> startItems;
	
	std::ifstream charactersFile("Characters/instances.txt");
	if(!charactersFile){
		throw fileNotFound("Characters/instances.txt");
	}
	std::string carname="waterBubble";

	std::vector<sf::Vector2i> spritePlayerData;
	std::vector<sf::Vector2i> spritePlayerAction;
	std::vector<std::string> spritePlayerNames;

	std::string currstring = "";

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
		
		currstring = "";

		charactersFile>>currstring;
		if((currstring.find("named")!= std::string::npos)){
			charactersFile>>currstring;
			name=currstring;
		}
		if((currstring.find("idleName")!= std::string::npos)){
			charactersFile>>currstring;
			idleName=currstring;
		}
		if((currstring.find("idleFile")!= std::string::npos)){
			charactersFile>>currstring;
			idleFile=currstring;
		}
		if((currstring.find("jumpName")!= std::string::npos)){
			charactersFile>>currstring;
			jumpName=currstring;
		}
		if((currstring.find("jumpFile")!= std::string::npos)){
			charactersFile>>currstring;
			jumpFile=currstring;
		}
		if((currstring.find("walkName")!= std::string::npos)){
			charactersFile>>currstring;
			walkName=currstring;
		}
		if((currstring.find("position")!= std::string::npos)){
			charactersFile>>position;
		}
		if((currstring.find("walkFile")!= std::string::npos)){
			charactersFile>>currstring;
			walkFile=currstring;
		}
		if((currstring.find("attackName")!= std::string::npos)){
			charactersFile>>currstring;
			attackName=currstring;
		}
		if((currstring.find("attackFile")!= std::string::npos)){
			charactersFile>>currstring;
			attackFile=currstring;
		}
		
		
		prevstring=currstring;
		if((currstring.find("eind")!= std::string::npos)){
			startItems.clear();
			SpriteCharacter characterData( idleName, idleFile, jumpName,  jumpFile,  walkName,  walkFile, attackName,  attackFile,  dieName,  dieFile);
			if(name=="player"){
				startItems.push_back(std::make_shared<Weapon>("ironSword", assets, 20, 300));
				startItems.push_back(std::make_shared<Weapon>("battleAxe", assets, 10, 500));
				startItems.push_back(std::make_shared<Weapon>("bigDagger", assets, 10, 500));
				startItems.push_back(std::make_shared<Consumable>("hunger", assets, 50));
				startItems.push_back(std::make_shared<Consumable>("hunger", assets, 50));
				startItems.push_back(std::make_shared<Block>("crate", assets, 0, event, world, window, view));
				characters.push_back(Character(position, std::make_shared<PlayerInput>(world, characters), std::make_shared<PhysicsComponent>(), std::make_shared<AnimatedPlayerGraphics>(name, assets, characterData), startItems, world, true));
			}else if (name =="orc"){
				startItems.push_back(std::make_shared<Weapon>("club", assets, 30, 1500));
				startItems.push_back(std::make_shared<Consumable>("hunger", assets, 70));
				characters.push_back(Character(position, std::make_shared<BossInput>(world, characters), std::make_shared<BossPhysics>(), std::make_shared<AnimatedGraphicsComponent>(name, assets, characterData), startItems, world,false,200));
			}else if (name =="dog"){
				startItems.push_back(std::make_shared<Weapon>("whip", assets, 15, 500));
				startItems.push_back(std::make_shared<Consumable>("hunger", assets, 50));
				characters.push_back(Character(position, std::make_shared<EnemyInput>(world, characters), std::make_shared<DogPhysics>(), std::make_shared<AnimatedGraphicsComponent>(name, assets, characterData), startItems, world,false));
			}else if (name !=""){
				startItems.push_back(std::make_shared<Weapon>("woodenSword", assets, 10, 500));
				startItems.push_back(std::make_shared<Consumable>("hunger", assets, 50));
				characters.push_back(Character(position, std::make_shared<EnemyInput>(world, characters), std::make_shared<EnemyPhysics>(), std::make_shared<AnimatedGraphicsComponent>(name, assets, characterData), startItems, world));
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
			position = {0,0};
			spritePlayerData.clear();
			spritePlayerNames.clear();
			spritePlayerAction.clear();
		}

	}
}