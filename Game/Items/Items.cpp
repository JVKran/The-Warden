/// @file

#include "Items.hpp"

/// \brief
/// Create weapon instance.
/// \details
/// This function creates a Weapon.
/// @param damageFactor The damagefactor to calculate damage dealt.
/// @param hitPeriod The period that should be in between attacks.
Weapon::Weapon(const int damageFactor, const int_fast16_t hitPeriod):
	hitPeriod(hitPeriod),
	damageFactor(damageFactor)
{}

/// \brief
/// Create consumable instance.
/// \details
/// This function creates a Consumable.
/// @param foodValue The foodvalue to calculate new amount of health.
Consumable::Consumable(const int_fast8_t foodValue):
	foodValue(foodValue)
{}

void Weapon::use(Character * character, std::vector<Character> & characters){
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
}

/// \brief
/// Replenish Character health.
/// \details
/// This function adds the foodValue to the Character's current health.
void Consumable::use(Character * character, std::vector<Character> & characters){
	character->setHealth(foodValue + character->getHealth());
	if(character->getHealth() > 100){
		character->setHealth(int_fast8_t(100));
	}
}