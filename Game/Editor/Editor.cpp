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
	//window.draw( tileSelectionBar );
	for( auto object : objects ){
		object.draw(window);
	}
}

void Editor::handleInput(sf::RenderWindow & window){
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right)){
		for(auto & object : objects){
			if(object.getBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window)))){
				if(!object.hasBeenAdded){
					SelectableObject objectToAdd = object;
					objectToAdd.setNewScale(1);
					world.addTile(objectToAdd);
					object.hasBeenAdded = true;
				}
			} else {
				object.hasBeenAdded = false;
			}
	    }
	}
    std::vector<SelectableObject> & tiles = world.getTiles();
    for(auto & tile : tiles){
    	if(tile.getBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window)))){
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && isFirstOneSelected(tiles)){
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
	sf::Vector2f position { 10, 10 };
	while( !isEmpty( objectInput ) ){
		objectInput >> name >> scale;
		objects.push_back(SelectableObject(name, assets, position, scale));
		position.y += 70;
	}
}	

bool Editor::isFirstOneSelected(std::vector<SelectableObject> & tiles){
	for(const auto & tile : tiles){
		if(tile.isFollowingMouse()){
			return false;
		}
	}
	return true;
}