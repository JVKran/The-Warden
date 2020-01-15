#include "Editor.hpp"
#include <SFML/Graphics.hpp>


Editor::Editor( AssetManager & assets, const std::string & worldFileName ):
	assets( assets ),
	world( assets, worldFileName )
{
	tileSelectionBar.setSize( sf::Vector2f{ 300, 840 } );
	tileSelectionBar.setPosition(50, 100);
	tileSelectionBar.setFillColor( sf::Color::Blue );
	loadObjects( objects );
}

bool Editor::isEmpty( std::ifstream & file ){
	return file.peek() == std::ifstream::traits_type::eof();
}

void Editor::editingDone(){
	world.saveWorld();
}

void Editor::draw( sf::RenderWindow & window ){
	world.draw( 0, 1000, window );	
	drawTileBar( window );
}

void Editor::drawTileBar( sf::RenderWindow & window ){
	window.draw( tileSelectionBar );
	uint_fast8_t rowObjectCounter = 0;
	sf::Vector2f position { 60, 110 };
	for( auto object : objects ){
		if( rowObjectCounter < 2 ){
			object.setPosition( position );
			position.x += 80;
			rowObjectCounter++;
		} else {
			rowObjectCounter = 0;
			position.x = 60;
			position.y += 80;
			object.setPosition( position.x, position.y );
		}
		window.draw( object );
	}
}

void Editor::loadObjects( std::vector< sf::Sprite > & objects, const std::string & editorConfigName ){
	std::ifstream objectInput(editorConfigName);
	std::string name;
	float scale;
	while( !isEmpty( objectInput ) ){
		objectInput >> name >> scale;
		sf::Sprite sprite;
		sprite.setTexture( assets.getTexture( name ) );
		sprite.setScale( scale, scale );
		objects.push_back( sprite );
	}
}	