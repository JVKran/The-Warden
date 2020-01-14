#include "Editor.hpp"
#include <SFML/Graphics.hpp>
Editor::Editor( AssetManager & assets ):
	assets( assets ),
	newWorld( assets )
{
	tileSelectionBar.setSize( size );
	createNewWorld();
}

void Editor::createNewWorld(){
	std::ofstream worldFile(worldName);
	worldFile << "background\n";
	worldFile << "(300, 300) crate";
	newWorld.loadWorld( "newWorld.txt" );
}

void Editor::draw( sf::RenderWindow & window ){
	tileSelectionBar.setPosition(50, 50);
	newWorld.draw( window );	
}