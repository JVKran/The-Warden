#ifndef __EDITOR_HPP
#define __EDITOR_HPP

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <cstring>
#include "World.hpp"
#include "AssetManager.hpp"
#include "ScreenObject.hpp"

class Editor {
private:
	AssetManager & assets;
	World newWorld;
	uint_fast8_t tileIndex = 0;
	std::string worldName = "newWorld.txt";
	sf::RectangleShape tileSelectionBar;
	sf::Vector2f size = { 300, 840 };
	std::vector< sf::Sprite > availableTiles;
	bool isEmpty(std::ifstream & file);
public:
	Editor( AssetManager & assets );
	void createNewWorld( const std::string & filename );
	std::vector< sf::Sprite > getObjectSprites( std::vector< sf::Sprite > & objects );
	void draw( sf::RenderWindow & window );
	void drawTileBar( sf::RenderWindow & window );
};

#endif // Editor.hpp