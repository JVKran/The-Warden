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

	std::vector< SelectableObject > objects;

	bool isFirstOneSelected(std::vector<SelectableObject> & tiles);
	bool isEmpty(std::ifstream & file);
public:
	Editor( AssetManager & assets, const std::string & worldFileName );

	void editingDone();
	void handleInput(sf::RenderWindow & window);

	void loadObjects( std::vector< SelectableObject > & objects, const std::string & editorConfigName = "editorObjects.txt");

	void draw( sf::RenderWindow & window );
	void drawTileBar( sf::RenderWindow & window );
};

#endif // Editor.hpp