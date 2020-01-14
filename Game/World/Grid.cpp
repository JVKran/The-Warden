#include "Grid.hpp"

void Grid::loadTile(std::ifstream & input){
	std::string assetName;
	sf::Vector2f position;
	float scale;
	input >> position >> assetName >> scale;
	if(position.x > largestIndex){
		for(uint_fast32_t i = largestIndex; i <= position.x / 100; i++){
			tiles.push_back();
		}
		largestIndex = position.x / 100;
	}
	tiles[position.x]push_back(ScreenObject(assetName, assets, position, scale));
}

void Grid::loadingDone(){
	std::sort(tiles.begin(), tiles.end());
}