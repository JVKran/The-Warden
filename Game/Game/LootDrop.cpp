#include "LootDrop.hpp"

LootDrop::LootDrop(World & world):
	world(world)
{}

void LootDrop::drop(std::vector<std::shared_ptr<Item>> & items, int_fast16_t experience, sf::Vector2f position){
	std::cout << "drop" << std::endl;
	for(std::shared_ptr<Item> item : items){
		item->setPosition(position);
		//world.addTile(*item);
		position.x += 30;
	}
}