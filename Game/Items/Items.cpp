/// @file

#include "Items.hpp"

/// \brief
/// Create an item.
/// \details
/// This function creates an item based on its parameters.
/// @param assetName The name of the asset this item should have.
/// @param assets The AssetManager to use for retrieving the asset identiefied by the passed assetName.
/// @param experience The amount of experience to give this item.
Item::Item(const std::string assetName, AssetManager & assets, int_fast8_t experience):
	Tile(assetName, assets),
	assetName(assetName),
	experience(experience)
{}

/// \brief
/// Is weapon?
/// \return Wether or not this item is a weapon.
bool Item::isWeapon() {
	return false;
}

/// \brief
/// Contains experience?
/// \return Wether or not this item contains experience.
bool Item::containsExperience() {
	return false;
}

/// \brief
/// Get experience.
/// \return The amount of experience this item has.
int_fast8_t Item::getExperience() {
	return experience;
}

/// \brief
/// Get hitperiod.
/// \return The time in milliseconds that has to be between two attacks.
int_fast16_t Item::getPeriod(){
	return 0;
}

/// \brief
/// Get name?
/// \return The name of the asset of this item.
std::string Item::getName(){
	return assetName;
}

/// \brief
/// Create weapon instance.
/// \details
/// This function creates a Weapon based on its parameters.
/// @param assetName The name of the asset this item should have.
/// @param assets The AssetManager to use for retrieving the asset identiefied by the passed assetName.
/// @param damageFactor The damagefactor to calculate damage dealt.
/// @param hitPeriod The period that should be in between attacks.
Weapon::Weapon(const std::string assetName, AssetManager & assets, const int damageFactor, const int_fast16_t hitPeriod):
	Item(assetName, assets),
	hitPeriod(hitPeriod),
	damageFactor(damageFactor)
{}

/// \brief
/// Get hitperiod.
/// \return The time in milliseconds that has to be between two attacks.
int_fast16_t Weapon::getPeriod(){
	return hitPeriod;
}

/// \brief
/// Attack
/// \details
/// This function attacks all Characters that are within range. If the hit Character is a player and his health is below zero, the player is respawned.
/// If the hit character is an Enemy and its health is below zero, the character dies. Furthermore, 10 experience points are added to the Character that hit
/// another Character.
/// @param character The character that is attacking.
/// @param characters All Characters that could be hit.
bool Weapon::use(Character * character, std::vector<Character> & characters){
	bool hasHit=false;
	for(int_fast8_t i = characters.size() -1; i >= 0; i--){
		if(*character != characters.at(i) && clock.getElapsedTime().asMilliseconds() - lastAttack.asMilliseconds() > hitPeriod){
			sf::FloatRect subject = characters.at(i).getBounds();
			if(character->getBounds().intersects(sf::FloatRect(subject.left-2,subject.top-2,subject.width+4,subject.height+4))&&!(!character->isPlayer()&&!characters.at(i).isPlayer())){
				lastAttack = clock.getElapsedTime();
				characters.at(i).setHealth( (characters.at(i).getHealth()) - damageFactor );
				if(characters.at(i).getHealth() < 0){
					try{
						if(characters.at(i).isPlayer()){
							characters.at(i).respawn();
							characters.at(i).setHealth(100);
						} else {
							characters.at(i).die();
							characters.erase( std::find(characters.begin(), characters.end(), characters.at(i)) );
						}
					} catch (const std::exception & error){
						std::cout << "(!)-- " << error.what() << std::endl;
					} catch (...){
						std::cout << "(!)-- Something went wrong..." << std::endl;
					}
				}
				character->addExperience(10);
				hasHit=true;
			}
		}
	}
	return hasHit;
}

/// \brief
/// Is weapon?
/// \return Wether or not this item is a weapon.
bool Weapon::isWeapon(){
	return true;
}

/// \brief
/// Create consumable instance.
/// \details
/// This function creates a Consumable.
/// @param assetName The name of the asset this item should have.
/// @param assets The AssetManager to use for retrieving the asset identiefied by the passed assetName.
/// @param foodValue The foodvalue to calculate new amount of health.
Consumable::Consumable(const std::string assetName, AssetManager & assets, const int_fast8_t foodValue):
	Item(assetName, assets),
	foodValue(foodValue)
{}

/// \brief
/// Replenish Character health.
/// \details
/// This function adds the foodValue to the Character's current health.
/// @param character The character that is using the consumable.
/// @param characters All Characters that could be hit (unused).
bool Consumable::use(Character * character, std::vector<Character> & characters){
	character->setHealth(foodValue + character->getHealth());
	std::cout << "(i)-- New player health " << foodValue + character->getHealth() << std::endl;
	if(character->getHealth() > 100){
		character->setHealth(100);
	}
	return true;
}

/// \brief
/// Create Experience instance.
/// \details
/// This function creates an Experience item based on its parameters.
/// @param assetName The name of the asset this item should have.
/// @param assets The AssetManager to use for retrieving the asset identiefied by the passed assetName.
/// @param experience The amount of experience to give this item.
Experience::Experience(const std::string assetName, AssetManager & assets, int_fast8_t experience):
	Item(assetName, assets, experience)
{}

/// \brief
/// Contains experience?
/// \return Wether or not this item contains experience.
bool Experience::containsExperience() {
	return true;
}

/// \brief
/// Get experience.
/// \return The amount of experience this item has.
int_fast8_t Experience::getExperience() {
	return experience;
}

/// \brief
/// Create block instance.
/// \details
/// This function creates a block item and is
/// also able to delete an object on which the mouse is located
/// and is a crate object.
/// @param assetName The name of the asset this item should have.
/// @param assets The AssetManager to use for retrieving the asset identiefied by the passed assetName.
/// @param amountOfObjects The amount of objects we are able to create.
/// @param event The sf::Event to use for determining wether or not a block should be placed or broken.
/// @param window The sf::RenderWindow the blockamount should be written into.
/// @param view The sf::View to use for determining the absolute position the mouse was clicked at.
Block::Block(const std::string assetName, AssetManager & assets, int_fast8_t amountOfObjects, const sf::Event & event, World & world, sf::RenderWindow & window, sf::View & view):
	Item(assetName, assets),
	amountOfObjects(amountOfObjects),
	assets(assets),
	event(event),
	world(world),
	window(window),
	view(view)
{
	setNewScale(0.27);												//sets the scale for inventory smaller, because othwise a to big crate will be visible in the inventory
	if (!blockFont.loadFromFile("Minecraft.ttf")){
	    std::cerr << "(!)-- Font Minecraft.ttf not found" << std::endl;
	} else {
		blockText.setFont(blockFont);
	}
	blockText.setScale(0.5, 0.5);
	blockText.setFillColor(sf::Color::White);
}

/// \brief
/// Create a tile.
/// \details
/// This function creates a new Tile object as long as amountOfObjects is bigger than 0,	
/// it will also delete a object if the mouse is on an already existing object. 
/// If the mouse is on a object it will also check if it is a crate, because
/// we only allow it to delete crates, because we don't want te player to destroy the
/// world.
bool Block::use(Character * character, std::vector<Character> & characters){
	std::vector<Tile> & objects = world.getTiles();				//takes a reference to the vector tiles in world

	//gets the distance between the player and the mouse
	float distance = std::sqrt(std::pow(window.mapPixelToCoords(sf::Mouse::getPosition(window), view).x - character->getPosition().x, 2) +  
               		 std::pow(window.mapPixelToCoords(sf::Mouse::getPosition(window), view).y - character->getPosition().y, 2) * 1.0); 

	//if the mouse is less than 300 blocks away from the player you are allowed to add blocks and destroy crates
	if(distance < 400){
		//goes through all objects to find a object that is a crate where the mouse is located on before deleting it.
		for(Tile & object : objects){			
			if(object.getBounds().contains(sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window), view)))){		//check if the mouse is on an existing object
				if(object.getName() == "crate"){											//only erases the object if it is a crate
					objects.erase( std::find(objects.begin(), objects.end(), object) );		//delete the object the mouse is on
					amountOfObjects++;														//adds a object if the mouse is on an existing object
					return false;															//return, so the next if statement doesn't need to be calculated/used
				}
				return false;																//also return false, when there is a collision with mouse, but not the right object
			}
		}

		//if the mouse is not on an already existing object and the amountOfObjects is still bigger than 0 it will create a new tile
		if(amountOfObjects > 0){						//can create new objects as long as there are more than 0 amountOfObjects
			Tile tile("crate", assets, sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window), view)));
			if(!character->getGlobal().intersects(tile.getBounds())){	//checks if the tile is inside the player
				characters.at(0).addTile(tile);							//creates new crate object
				amountOfObjects--;										//decreases the amount of objects that can be created
			}				
			return false;												//return false as long as we can create objects
		}else{
			return false;												//return true when there are no objects to create anymore
		}
	}
	return false;
}

/// \brief
/// Draw amount of blocks
/// \details
/// This function draws the amount of blocks in the same space the block item icon is drawn in the Character's inventory.
void Block::drawAmount(sf::RenderWindow & window){
	blockText.setString(std::to_string(getAmount()));
	blockText.setPosition(sf::Vector2f(sprite.getPosition().x + 2, sprite.getPosition().y + 2));
	window.draw(blockText);
}
