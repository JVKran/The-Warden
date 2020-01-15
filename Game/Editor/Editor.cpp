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
	for( auto object : objects ){
		object.draw(window);
	}
}

void Editor::handleInput(sf::RenderWindow & window){
	for(auto & object : objects){
		if(object.getBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window)))){
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				if(object.setFollowMouse(true)){
					world.addTile(object);
					objects.erase(std::remove(objects.begin(), objects.end(), object), objects.end());
				}
			}
			if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
				object.setFollowMouse(false);
			}
		}
    	object.move(sf::Mouse::getPosition(window));
    }
    std::vector<SelectableObject> & tiles = world.getTiles();
    for(auto & tile : tiles){
    	if(tile.getBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window)))){
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				tile.setFollowMouse(true);
			}
			if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
				tile.setFollowMouse(false);
			}
		}
    	tile.move(sf::Mouse::getPosition(window));
    }
}

void Editor::loadObjects( std::vector< SelectableObject > & objects, const std::string & editorConfigName ){
	std::ifstream objectInput(editorConfigName);
	std::string name;
	float scale;
	uint_fast16_t rowObjectCounter = 0;
	sf::Vector2f position { 60, 110 };
	while( !isEmpty( objectInput ) ){
		if( rowObjectCounter < 2 ){
			position.x += 80;
			rowObjectCounter++;
		} else {
			rowObjectCounter = 0;
			position.x = 60;
			position.y += 80;
		}
		objectInput >> name >> scale;
		objects.push_back(SelectableObject(name, assets, position, scale));
	}
}	