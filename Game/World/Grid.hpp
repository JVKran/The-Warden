#ifndef __GRID_HPP
#define __GRID_HPP

#include <vector>
#include "ScreenObject.hpp"
#include "../exceptions.hpp"
#include "AssetManager.hpp"

class Grid {
	private:
		AssetManager & assets;
		std::vector<ScreenObject> tiles;
	public:
		Grid(AssetManager & assets);

		void loadTile(std::ifstream & input);
		void loadingDone();

		void draw(const float leftPosition, const float rightPosition, sf::RenderWindow & window);
};

#endif //__GRID_HPP