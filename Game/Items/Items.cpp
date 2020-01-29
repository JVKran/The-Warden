/// @file

#include "Items.hpp"

bool Item::isWeapon() {
	return false;
}
bool Item::containsExperience() {
	return false;
}

int_fast8_t Item::getExperience() {
	return experience;
}
/// \brief
/// Create weapon instance.
/// \details
/// This function creates a Weapon.
/// @param damageFactor The damagefactor to calculate damage dealt.
/// @param hitPeriod The period that should be in between attacks.
Weapon::Weapon(const std::string assetName, AssetManager & assets, const int damageFactor, const int_fast16_t hitPeriod):
	Item(assetName, assets),
	hitPeriod(hitPeriod),
	damageFactor(damageFactor)
{}

/// \brief
/// Create consumable instance.
/// \details
/// This function creates a Consumable.
/// @param foodValue The foodvalue to calculate new amount of health.
Consumable::Consumable(const std::string assetName, AssetManager & assets, const int_fast8_t foodValue):
	Item(assetName, assets),
	foodValue(foodValue)
{}

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

bool Weapon::isWeapon(){
	return true;
}

/// \brief
/// Replenish Character health.
/// \details
/// This function adds the foodValue to the Character's current health.
bool Consumable::use(Character * character, std::vector<Character> & characters){
	character->setHealth(foodValue + character->getHealth());
	std::cout << "New health " << foodValue + character->getHealth() << std::endl;
	if(character->getHealth() > 100){
		character->setHealth(100);
	}
	return true;
}

Experience::Experience(const std::string assetName, AssetManager & assets, int_fast8_t experience):
	Item(assetName, assets, experience)
{}

bool Experience::containsExperience() {
	return true;
}

/// \brief
/// Return the experience.
/// \details
/// Return the amount of experience the experience Item has.
int_fast8_t Experience::getExperience() {
	return experience;
}

/// \brief
/// Create block instance.
/// \details
/// This function creates a block item and is
/// also able to delete an object on which the mouse is located
/// and is a crate object
/// @param amountOfObjects The amount of objects we are able to create
Block::Block(const std::string assetName, AssetManager & assets, int_fast8_t amountOfObjects, const sf::Event & event, World & world, sf::RenderWindow & window, sf::View & view):
	Item(assetName, assets),
	amountOfObjects(amountOfObjects),
	assets(assets),
	event(event),
	world(world),
	window(window),
	view(view)
{
	setNewScale(0.27);		//sets the scale for inventory smaller, because othwise a to big crate will be visible in the inventory
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
	std::vector<Tile> & objects = world.getTiles();				//takes a reference from the vector tiles in world

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