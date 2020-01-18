/// @file

#ifndef __EDITOR_HPP
#define __EDITOR_HPP

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <cstring>
#include "World.hpp"
#include "AssetManager.hpp"
#include "ScreenObject.hpp"

/// \brief
/// World Editor
/// \details
/// This class features the ability to edit worlds. This is done using a Drag & Drop interface
/// enabling both players and developers to easily create playable worlds.
class Editor {
private:
	AssetManager & assets;											//!< The AssetManager to use for gathering the needed textures.
	World world;													//!< The World to edit.

	sf::View & view;
	sf::Event & event;												//!< The view to use for scrolling through the world.

	std::vector< Tile > objects;						//!< Vector with all placeable objects.

	bool isFirstOneSelected(std::vector<Tile> & tiles);
public:
	Editor( AssetManager & assets, sf::View & view, sf::Event & event );

	void selectWorld(const std::string & worldName);

	void editingDone();
	void handleInput(sf::RenderWindow & window);

	void loadObjects(const std::string & editorConfigName = "Editor/editorObjects.txt");

	void draw(sf::RenderWindow & window);
	void drawTileBar( sf::RenderWindow & window );
	void scrollTileBar( const int_fast16_t & mouseWheelDelta );
};

#endif // Editor.hpp