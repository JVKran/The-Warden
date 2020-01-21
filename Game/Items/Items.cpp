#include "Items.hpp"

Weapon::Weapon(const uint_fast8_t damageFactor):
	damageFactor(damageFactor)
{}

Consumable::Consumable(const uint_fast16_t foodValue):
	foodValue(foodValue)
{}

void Weapon::use(Character * character, std::vector<Character> & characters){
	for(Character & comparingCharacter : characters){
		if(*character != comparingCharacter){
			if(character->getBounds().intersects(comparingCharacter.getBounds())){
				std::cout << "Hit character!" << std::endl;
			}
		}
	}
}

void Consumable::use(Character * character, std::vector<Character> & characters){
	character->health += foodValue;
	if(character->health > 100){
		character->health = 100;
	}
}
