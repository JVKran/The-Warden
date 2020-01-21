#include "Items.hpp"

Weapon::Weapon(const int_fast8_t damageFactor):
	damageFactor(damageFactor)
{}

Consumable::Consumable(const uint_fast8_t foodValue):
	foodValue(foodValue)
{}

void Weapon::use(Character * character, std::vector<Character> & characters){
	for(Character & comparingCharacter : characters){
		if(*character != comparingCharacter){
			if(character->getBounds().intersects(comparingCharacter.getBounds())){
				std::cout << "Hit character!" << std::endl;
				character->setHealth(character->getHealth() - damageFactor);
			}
		}
	}
}

void Consumable::use(Character * character, std::vector<Character> & characters){
	character->setHealth(foodValue + character->getHealth());
	if(character->getHealth() > 100){
		character->setHealth(int_fast8_t(100));
	}
}
