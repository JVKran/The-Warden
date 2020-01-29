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
	sf::RenderWindow & window;
	std::vector<KeyBinding> & bindings; 

	std::vector< Tile > objects;						//!< Vector with all placeable objects.
	int_fast32_t leftBound;
	int_fast32_t rightBound;

	bool isFirstOneSelected(std::vector<Tile> & tiles);
	void drawTileBar( sf::View & view );
	void scrollTileBar( const int_fast16_t & mouseWheelDelta );
	void handleObjectInput(Tile & tile, sf::RenderWindow & window, sf::View & view, const sf::Event & event);
	void handleTileInput(Tile & tile, sf::RenderWindow & window, sf::View & view, std::vector<Tile> & tiles);
public:
	Editor( sf::RenderWindow & window, AssetManager & assets, std::vector<KeyBinding> & bindings  );

	void selectWorld(const std::string & worldName);

	void editingDone();
	void handleInput( sf::View & view);
	void handleEvent(const sf::Event & event, sf::View & view);

	void loadObjects(const std::string & editorConfigName = "Editor/editorObjects.txt");

	void draw(sf::View & view);
};

#endif // Editor.hpp