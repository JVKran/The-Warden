#ifndef __EDITOR_HPP
#define __EDITOR_HPP

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <cstring>
#include "World.hpp"
#include "AssetManager.hpp"
#include "ScreenObject.hpp"

class SelectableObject : public ScreenObject {
	private:
		bool followMouse = false;
	public:
		SelectableObject(const std::string & assetName, AssetManager & assets, const sf::Vector2f & position, const float scale);

		void setFollowMouse(const bool follow);

		void move(const sf::Vector2i & position);

		SelectableObject& operator=(SelectableObject lhs);
};

class Editor {
private:
	AssetManager & assets;
	World world;
	sf::RectangleShape tileSelectionBar;

	std::vector< SelectableObject > objects;
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