/// @file

#include "Items.hpp"

bool Item::isWeapon() {
	return false;
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
	for(int_fast8_t i = characters.size() - 1; i >= 0; i--){
		if(*character != characters.at(i) && clock.getElapsedTime().asMilliseconds() - lastAttack.asMilliseconds() > hitPeriod){
			lastAttack = clock.getElapsedTime();
			if(character->getBounds().intersects(characters.at(i).getBounds())){
				characters.at(i).setHealth( (characters.at(i).getHealth()) - damageFactor );
				if(characters.at(i).getHealth() < 0){
					try{
						if(characters.at(i).isPlayer()){
							characters.at(i).respawn();
							characters.at(i).setHealth(100);
						} else {
							characters.erase( std::find(characters.begin(), characters.end(), characters.at(i)) );
						}
					} catch (const std::exception & error){
						std::cout << "(!)-- " << error.what() << std::endl;
					} catch (...){
						std::cout << "(!)-- Something went wrong..." << std::endl;
					}
					return true;
				}
			}
		}
	}
	return false;
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
	if(character->getHealth() > 100){
		character->setHealth(100);
	}
	return true;
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
	event(event),
	world(world),
	window(window),
	view(view)
{}

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

	//goes through all objects to find a object that is a crate where the mouse is located on before deleting it.
	for(Tile & object : objects){			
		if(object.getBounds().contains(sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window), view)))){		//check if the mouse is on an existing object
			if(object.getName() == "crate"){											//only erases the object if it is a crate
				objects.erase( std::find(objects.begin(), objects.end(), object) );		//delete the object the mouse is on
				amountOfObjects++;														//adds a object if the mouse is on an existing object
				return false;															//return, so the next if statement doesn't need to be calculated/used
			}
			return false;
		}
	}

	//if the mouse is not on an already existing object and the amountOfObjects is still bigger than 0 it will create a new tile
	if(amountOfObjects > 0){										//can create new objects as long as there are more than 0 amountOfObjects
		characters.at(0).addTile(event, world, window, view);		//creates new crate object
		amountOfObjects--;											//decreases the amount of objects that can be created					
		return false;												//return false as long as we can create objects
	}else{
		return false;												//return true when there are no objects to create anymore
	}
}