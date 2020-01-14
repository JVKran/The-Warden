#ifndef __EDITOR_HPP
#define __EDITOR_HPP

#include < SFML/Grahpics.hpp >
#include < ../exceptions.hpp >
#include < array >
#include "World.hpp"
#include "AssetManager.hpp"
#include "Screenobject.hpp"

class Editor {
private:
	AssetManager & assets;
	World newWorld;
	vector< Screenobject > availableTiles;
	uint_fast8_t tileIndex = 0;
	
public:
	Editor( AssetManager & assets );
	void draw( sf::RenderWindow & window );
};

#endif // Editor.hpp