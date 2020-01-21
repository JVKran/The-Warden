#include "Items.hpp"

Weapon::Weapon(const int damageFactor, const int_fast16_t hitPeriod):
	hitPeriod(hitPeriod),
	damageFactor(damageFactor)
{}

Consumable::Consumable(const int foodValue):
	foodValue(foodValue)
{}

void Weapon::use(Character * character, std::vector<Character> & characters){
	for(Character & comparingCharacter : characters){
		if(*character != comparingCharacter && clock.getElapsedTime().asMilliseconds() - lastAttack.asMilliseconds() > hitPeriod){
			lastAttack = clock.getElapsedTime();
			if(character->getBounds().intersects(comparingCharacter.getBounds())){
				character->setHealth( (character->getHealth()) - damageFactor );
				if(character->getHealth() < 0){
					characters.erase(std::find(characters.begin(), characters.end(), comparingCharacter));
				}
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
