#ifndef __EDITOR_HPP
#define __EDITOR_HPP

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include "World.hpp"
#include "AssetManager.hpp"
#include "ScreenObject.hpp"

class Editor {
public:
	AssetManager & assets;
	World newWorld;
	std::vector< ScreenObject > availableTiles;
	uint_fast8_t tileIndex = 0;
	std::string worldName = "newWorld.txt";
	sf::RectangleShape tileSelectionBar;
	sf::Vector2f size = { 50, 100 };
public:
	Editor( AssetManager & assets );
	void createNewWorld();
	void draw( sf::RenderWindow & window );
};

#endif // Editor.hpp