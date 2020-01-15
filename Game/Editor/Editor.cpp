#include "Editor.hpp"
#include <SFML/Graphics.hpp>


Editor::Editor( AssetManager & assets ):
	assets( assets ),
	newWorld( assets )
{
	tileSelectionBar.setSize( size );
	tileSelectionBar.setFillColor( sf::Color::Blue );
	// std::ofstream worldFile(worldName);
	// worldFile << "\nbackground\n";
	// worldFile << "(800, 200) crate 1";
	getObjectSprites( availableTiles );
	createNewWorld( "newWorld.txt" );
}

bool Editor::isEmpty( std::ifstream & file ){
	return file.peek() == std::ifstream::traits_type::eof();
}

void Editor::createNewWorld( const std::string & filename ){
	newWorld.loadWorld( filename );
}

void Editor::draw( sf::RenderWindow & window ){
	tileSelectionBar.setPosition(50, 100);
	newWorld.draw( 0, 1000, window );	
	drawTileBar( window );
}

void Editor::drawTileBar( sf::RenderWindow & window ){
	window.draw( tileSelectionBar );
	uint_fast8_t rowObjectCounter = 0;
	sf::Vector2f position { 60, 110 };
	for( auto object : availableTiles ){
		if( rowObjectCounter < 2 ){
			object.setPosition( position );
			position.x += 140;
			rowObjectCounter++;
		} else {
			rowObjectCounter = 0;
			position.x = 60;
			position.y += 140;
			object.setPosition( position.x, position.y );
		}
		window.draw( object );
	}
}

std::vector< sf::Sprite > Editor::getObjectSprites( std::vector< sf::Sprite > & objects ){
	std::ifstream objectInput("editorObjects.txt");
	std::string name;
	float scale;
	while( !isEmpty( objectInput ) ){
		objectInput >> name >> scale;
			sf::Sprite sprite;
			sprite.setTexture( assets.getTexture( name ) );
			sprite.setScale( scale, scale );
			objects.push_back( sprite );
	}
	return objects;
}	