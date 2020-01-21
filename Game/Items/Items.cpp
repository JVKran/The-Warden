/// @file

#include "Items.hpp"

/// \brief
/// Create weapon instance.
/// \details
/// This function creates a Weapon.
/// @param damageFactor The damagefactor to calculate damage dealt.
Weapon::Weapon(const int_fast8_t damageFactor):
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
	for(Character & comparingCharacter : characters){
		if(*character != comparingCharacter){
			if(character->getBounds().intersects(comparingCharacter.getBounds())){
				std::cout << "Hit character!" << std::endl;
				// std::cout << character->getHealth() << std::endl;
				character->setHealth( (character->getHealth()) - damageFactor );
				if(character->getHealth() < 0){
					characters.erase(std::find(characters.begin(), characters.end(), comparingCharacter));
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
