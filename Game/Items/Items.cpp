#include "Items.hpp"

Weapon::Weapon(const uint_fast8_t damageFactor):
	damageFactor(damageFactor)
{}

Consumable::Consumable(const uint_fast8_t foodValue):
	foodValue(foodValue)
{}

void Weapon::use(Character & character, std::vector<Character> & characters){}

void Consumable::use(Character & character, std::vector<Character> & characters){
	character.setHealth(foodValue + character.getHealth());
	if(character.getHealth() > 100){
		character.setHealth(int_fast8_t(100));
	}
}
