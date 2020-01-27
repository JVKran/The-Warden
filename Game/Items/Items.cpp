/// @file

#include "Items.hpp"

bool Item::isWeapon() {
	return false;
}
bool Item::containsExperience() {
	return false;
}

uint_fast8_t Item::getExperience() {
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
							characters.at(i).die();
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
	std::cout<<assetName<<'\n';
	character->setHealth(foodValue + character->getHealth());
	if(character->getHealth() > 100){
		character->setHealth(100);
	}
	return true;
}

Experience::Experience(const std::string assetName, AssetManager & assets, uint_fast8_t experience):
	Item(assetName, assets, experience)
{}

bool Experience::containsExperience() {
	return true;
}

/// \brief
/// Return the experience.
/// \details
/// Return the amount of experience the experience Item has.
uint_fast8_t Experience::getExperience() {
	return experience;
}