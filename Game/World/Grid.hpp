#ifndef __GRID_HPP
#define __GRID_HPP

#include <vector>
#include <array>
#include "ScreenObject.hpp"

class Grid {
	private:
		uint_fast32_t largestIndex = 0;
		std::vector<std::array<ScreenObject, 100>> tiles;
	public:
		void loadTile(std::ifstream & input);
		void loadingDone();

};

#endif //__GRID_HPP