#include "Grid.hpp"

void Grid::loadTile(std::ifstream & input){
	std::string assetName;
	sf::Vector2f position;
	float scale;
	input >> position >> assetName >> scale;
	if(position.x / 100 > largestIndex){
		tiles.reserve(position.x / 100);
	}
	if(tiles[position.x / 100].size() == 20){
		throw storageSizeReached(20);
	}
	tiles[position.x / 100][tiles[position.x / 100].size()] = ScreenObject(assetName, assets, position, scale);
}

void Grid::loadingDone(){
	std::sort(tiles.begin(), tiles.end());
}

void Grid::draw(const float leftPosition, const float rightPosition, sf::RenderWindow & window){
	for(uint_fast32_t i = (leftPosition / 100) - 100; i < (rightPosition / 100) + 100; i++){
		for(const auto & tile : tiles[i]){
			tile.draw(window);
		}
	}
}