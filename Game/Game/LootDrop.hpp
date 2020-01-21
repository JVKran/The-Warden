#ifndef __LOOTDROP_HPP
#define __LOOTDROP_HPP

#include <vector>
#include "Items.hpp"

class Item;

class LootDrop{
	public:
		void drop(std::vector<Item> & items, const int experience);
};

#endif // LootDrop.hpp