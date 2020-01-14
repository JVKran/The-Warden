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
	getObjectSprites();
	createNewWorld( "newWorld.txt" );
}

void Editor::createNewWorld( const std::string & filename ){
	
	newWorld.loadWorld( filename );
}

void Editor::draw( sf::RenderWindow & window ){
	tileSelectionBar.setPosition(50, 100);
	newWorld.draw( window );	
	window.draw(tileSelectionBar);
	// std::vector<std::string> names= { "crate", "grass", "water" };
	// int len = names.size()-1;
	// int n = 0;
	// while( n!= len ){
	// 	for( int i=75; i < 300; i+= 150){
	// 		for( int j=125; j < 1000; j+= 150){
	// 			sf::Sprite sprite;
	// 			sprite.setPosition(i, j);
	// 			sprite.setTexture( assets.getTexture(names[n]));
	// 			window.draw(sprite);
	// 		}
	// 		n++;
	// 	}
	// }
}

std::vector< sf::Sprite > Editor::getObjectSprites(){
	std::ifstream objectInput;
	objectInput.open("objects.txt");
	std::vector< sf::Sprite > objects;
	std::string name, filename;
	try{
		while( !objectInput.eof()){
			objectInput >> name >> filename;
			std::cout << name;
		}
	}catch(...){
		std::cout << "...";
	}
	return objects;
}	