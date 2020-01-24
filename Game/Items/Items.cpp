/// @file

#include "Items.hpp"

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
	for(Character & characterToHit : characters){
		if(*character != characterToHit && clock.getElapsedTime().asMilliseconds() - lastAttack.asMilliseconds() > hitPeriod){
			lastAttack = clock.getElapsedTime();
			if(character->getBounds().intersects(characterToHit.getBounds())){
				characterToHit.setHealth( (characterToHit.getHealth()) - damageFactor );
				if(characterToHit.getHealth() < 0){
					try{
						characters.erase( std::find(characters.begin(), characters.end(), characterToHit) );
					} catch (const std::exception & error){
						std::cout << "(!)-- " << error.what() << std::endl;
					} catch (...){
						std::cout << "(!)-- Something went wrong..." << std::endl;
					}
				}
			}
		}
	}
	return false;

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
/// This function creates a block item.
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
/// This function creates a new Tile object as long as amountOfObjects is bigger than 0	
bool Block::use(Character * character, std::vector<Character> & characters){
	std::vector<Tile> & objects = world.getTiles();

	if(true){
		for(Tile & object : objects){
			if(object.getBounds().contains(sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window), view)))){
				objects.erase( std::find(objects.begin(), objects.end(), object) );
				amountOfObjects++;
				return false;
			}
		}
	}
	if(amountOfObjects > 0){										//can create new objects as long as there are more than 0 amountOfObjects
		characters.at(0).addTile(event, world, window, view);		//creates new crate object
		amountOfObjects--;											//decreases the amount of objects that can be created					
		return false;												//return false as long as we can create objects
	}else{
		return false;												//return true when there are no objects to create anymore
	}
}