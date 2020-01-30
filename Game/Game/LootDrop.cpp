/// @file

#include "LootDrop.hpp"

/// \brief
/// Create an instance.
/// \details
/// This creates a LootDrop instance by setting a refrence to the world.
/// @param world The World to add the items to when the loot is dropped.
LootDrop::LootDrop(World & world):
	world(world)
{}

/// \brief
/// Drop items and experience.
/// \details
/// This creates several items and adds these created items to the world.
/// @param items The items to place in the world.
/// @param experience The experience to drop. A new item is created for this.
/// @param position The position to start dropping items from.
void LootDrop::drop(std::vector<std::shared_ptr<Item>> items, int_fast16_t experience, sf::Vector2f position){
	items.push_back(std::make_shared<Experience>("experience", world.getAssets(), experience));
	std::cout << experience << std::endl;
	for(std::shared_ptr<Item> item : items){
		item->setPosition(position);
		world.addItem(item);
		position.x += 30;
	}
}