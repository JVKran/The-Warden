#ifndef __GRID_HPP
#define __GRID_HPP

#include <vector>
#include <array>
#include "ScreenObject.hpp"
#include "exceptions.hpp"

class Grid {
	private:
		uint_fast32_t largestIndex = 0;
		std::vector<std::array<ScreenObject, 20>> tiles;
	public:
		void loadTile(std::ifstream & input);
		void loadingDone();

		void draw(const float leftPosition, const float rightPosition, sf::RenderWindow & window);

};

#endif //__GRID_HPP