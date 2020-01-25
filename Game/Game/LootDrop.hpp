#ifndef __LOOTDROP_HPP
#define __LOOTDROP_HPP

#include <vector>
#include "Items.hpp"
#include <memory>
#include "World.hpp"

class Item;
class World;

class LootDrop {
	private:
		World & world;
	public:
		LootDrop(World & world);

		void drop(std::vector<std::shared_ptr<Item>> items, int_fast16_t experience, sf::Vector2f position);
};

#endif // LootDrop.hpp