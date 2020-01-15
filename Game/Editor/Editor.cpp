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
	newWorld.draw( window );	
	drawTileBar( window );
}

void Editor::drawTileBar( sf::RenderWindow & window ){
	window.draw( tileSelectionBar );
	uint_fast8_t rowObjectCounter = 0;
	uint_fast16_t xPosition = 60;
	uint_fast16_t yPosition = 110;
	for( auto object : availableTiles ){
		if( rowObjectCounter < 5 ){
			object.setPosition( xPosition, yPosition );
			yPosition += 140;
			rowObjectCounter++;
		} else if( rowObjectCounter == 5 ){
			object.setPosition( xPosition, yPosition );
			xPosition = 240;
			yPosition = 60;
			rowObjectCounter = 0;
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