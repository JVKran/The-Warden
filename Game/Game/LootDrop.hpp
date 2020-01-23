#ifndef __LOOTDROP_HPP
#define __LOOTDROP_HPP

#include <vector>
#include "Items.hpp"
#include <memory>

class Item;

class LootDrop{
	private:
		World & world;
	public:
		LootDrop(World & world):
			world(world)
		{}

		void drop(std::vector<std::shared_ptr<Item>> & items, int_fast16_t experience){
			std::cout << "drop" << std::endl;
		}
};

#endif // LootDrop.hpp