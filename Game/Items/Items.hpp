/// @file

#ifndef __ITEMS_HPP
#define __ITEMS_HPP

#include <vector>
#include <cstdint>
#include "Character.hpp"
#include <memory>
#include <functional>

class Character; 

/// \brief
/// Item
/// \details
/// This class is an abstract virtual class for all items.
class Item : public Tile {
	protected:
		const std::string assetName;
		int_fast8_t experience;
	public:
		Item(const std::string assetName, AssetManager & assets, int_fast8_t experience = 0):
			Tile(assetName, assets),
			assetName(assetName),
			experience(experience)
		{}
		virtual bool use(Character * character, std::vector<Character> & characters){return false;};
		virtual bool containsExperience();
		virtual int_fast8_t getExperience();
		virtual bool isWeapon();
		virtual int_fast16_t getPeriod(){
			return 0;
		}
		std::string getName(){
			return assetName;
		}
};

/// \brief
/// Weapon
/// \details
/// This class is responsible for hitting other existing Characters.
class Weapon : public Item {
	private:	
		sf::Clock clock;
		sf::Time lastAttack;
		const int_fast16_t hitPeriod;

		const int damageFactor;
	public:
		Weapon(const std::string assetName, AssetManager & assets, const int damageFactor, const int_fast16_t hitPeriod);
		virtual bool use(Character * character, std::vector<Character> & characters) override;
		virtual bool isWeapon() override;
		virtual int_fast16_t getPeriod() override{
			return hitPeriod;
		}
};

/// \brief
/// Consumable
/// \details
/// This class is responsible for replenishing health after the Character consumes a consumable.
class Consumable : public Item {
	private:
		const int_fast8_t foodValue;
	public:
		Consumable(const std::string assetName, AssetManager & assets, const int_fast8_t foodValue);
		virtual bool use(Character * character, std::vector<Character> & characters) override;
};

class Experience : public Item {
	public:
		Experience(const std::string assetName, AssetManager & assets, int_fast8_t experience = 0);
		virtual bool containsExperience() override;
		virtual int_fast8_t getExperience() override;
};

#endif //Items.hpp