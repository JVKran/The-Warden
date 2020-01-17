#ifndef _CSCREEN_HPP
#define _CSCREEN_HPP

#include <SFML/Graphics.hpp>
#include <string>

class cScreen {
public:

	virtual int Run ( sf::RenderWindow &window ) = 0;

};

#endif
