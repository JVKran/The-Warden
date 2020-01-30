/// @file

#ifndef __LOOTDROP_HPP
#define __LOOTDROP_HPP

#include <vector>
#include "Items.hpp"
#include <memory>
#include "World.hpp"

class Item;
class World;

/// \brief
/// Lootdrop
/// \details
/// This class features the lootdrop. It consists of creating items based on the given parameters.
/// These items are then added to the World so they can be picked up later on.
class LootDrop {
	private:
		World & world;					//!< The world to drop the items into.
	public:
		LootDrop(World & world);

		void drop(std::vector<std::shared_ptr<Item>> items, int_fast16_t experience, sf::Vector2f position);
};

#endif // LootDrop.hpp