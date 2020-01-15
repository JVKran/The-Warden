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
	World world;
	sf::RectangleShape tileSelectionBar;

	std::vector< sf::Sprite > objects;
	bool isEmpty(std::ifstream & file);
public:
	Editor( AssetManager & assets, const std::string & worldFileName );

	void editingDone();

	void loadObjects( std::vector< sf::Sprite > & objects, const std::string & editorConfigName = "editorObjects.txt");

	void draw( sf::RenderWindow & window );
	void drawTileBar( sf::RenderWindow & window );
};

#endif // Editor.hpp