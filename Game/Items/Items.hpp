/// @file

#ifndef __ITEMS_HPP
#define __ITEMS_HPP

#include <vector>
#include <cstdint>
#include "Character.hpp"
#include "World.hpp"
#include <memory>
#include <functional>
#include <cmath> 

class Character; 
class World;

/// \brief
/// Item
/// \details
/// This class is an abstract virtual class for all items.
class Item : public Tile {
	private:
		uint_fast8_t experience;
	public:
		Item(const std::string assetName, AssetManager & assets, uint_fast8_t experience = 0):
			Tile(assetName, assets)
		{}
		virtual bool use(Character * character, std::vector<Character> & characters){return false;};
		virtual bool containsExperience() {return false;};
		virtual uint_fast8_t getExperience() {return experience;};
		virtual bool isWeapon();
		virtual int_fast16_t getPeriod(){
			return 0;
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
		Experience(const std::string assetName, AssetManager & assets, uint_fast8_t experience = 30);
		virtual bool containsExperience() override {return true;};
		virtual uint_fast8_t getExperience() override {return getExperience();};
};

/// \brief
/// Block
/// \details
/// This class is responsible for placing blocks.
class Block : public Item {
	private:
		int_fast8_t amountOfObjects;		//!< The amount of blocks the player can hold
		AssetManager & assets;
		const sf::Event & event; 			//!< Needs an event for the use function
		World & world;						//!< Needs a world to add the blocks into the world
		sf::RenderWindow & window;			//!< Needs a window for the use function
		sf::View & view;					//!< Needs a view to get the right mouse position in the use function

	public:
		Block(const std::string assetName, AssetManager & assets, int_fast8_t amountOfObjects, const sf::Event & event, World & world, sf::RenderWindow & window, sf::View & view);
		virtual bool use(Character * character, std::vector<Character> & characters) override;
};

#endif //Items.hpp