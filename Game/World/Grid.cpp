#include "Grid.hpp"

std::ifstream & operator>>( std::ifstream & input, sf::Vector2f & rhs );

Grid::Grid(AssetManager & assets):
	assets(assets)
{}

void Grid::loadTile(std::ifstream & input){
	std::string assetName;
	sf::Vector2f position;
	float scale;
	input >> position >> assetName >> scale;
	tiles.push_back(ScreenObject(assetName, assets, position, scale));
}

void Grid::loadingDone(){
	std::sort(tiles.begin(), tiles.end(), [](const ScreenObject & a, const ScreenObject & b)->bool{
		return a.getPosition().x > b.getPosition().x;
	});
}

void Grid::draw(const float leftPosition, const float rightPosition, sf::RenderWindow & window){
	for(ScreenObject & tile : tiles){
		if(tile.getPosition().x + 100 > leftPosition && tile.getPosition().x - 100 < rightPosition){
			tile.draw(window);
			std::cout << tile.getPosition().x << std::endl;
		}
	}
}
std::vector<ScreenObject> Grid::getTiles(){
	return(tiles);
}