#include "LootDrop.hpp"

LootDrop::LootDrop(World & world):
	world(world)
{}

void LootDrop::drop(std::vector<std::shared_ptr<Item>> items, int_fast16_t experience, sf::Vector2f position){
	items.push_back(std::make_shared<Experience>("experience", world.getAssets(), experience));
	std::cout << experience << std::endl;
	position.x -= 100;
	for(std::shared_ptr<Item> item : items){
		item->setPosition(position);
		world.addItem(item);
		position.x += 30;
	}
}