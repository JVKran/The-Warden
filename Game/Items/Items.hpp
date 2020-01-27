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
	public:
		Item(const std::string assetName, AssetManager & assets):
			Tile(assetName, assets)
		{}
		virtual bool use(Character * character, std::vector<Character> & characters) = 0;
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

/// \brief
/// Block
/// \details
/// This class is responsible for placing blocks.
class Block : public Item {
	private:
		int_fast8_t amountOfObjects;		//!< The amount of blocks the player can hold
		const sf::Event & event; 			//!< Needs an event for the use function
		World & world;						//!< Needs a world to add the blocks into the world
		sf::RenderWindow & window;			//!< Needs a window for the use function
		sf::View & view;					//!< Needs a view to get the right mouse position in the use function

	public:
		Block(const std::string assetName, AssetManager & assets, int_fast8_t amountOfObjects, const sf::Event & event, World & world, sf::RenderWindow & window, sf::View & view);
		virtual bool use(Character * character, std::vector<Character> & characters) override;
};

#endif //Items.hpp