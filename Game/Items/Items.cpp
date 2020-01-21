#include "Items.hpp"

Weapon::Weapon(const int damageFactor):
	damageFactor(damageFactor)
{}

Consumable::Consumable(const int foodValue):
	foodValue(foodValue)
{}

void Weapon::use(Character * character, std::vector<Character> & characters){
	for(Character & comparingCharacter : characters){
		if(*character != comparingCharacter){
			if(character->getBounds().intersects(comparingCharacter.getBounds())){
				std::cout << "Hit character!" << std::endl;
				std::cout << character->getHealth() << std::endl;
				character->setHealth(character->getHealth() - damageFactor);
			}
		}
	}
}

void Consumable::use(Character * character, std::vector<Character> & characters){
	character->setHealth(foodValue + character->getHealth());
	if(character->getHealth() > 100){
		character->setHealth(100);
	}
}
