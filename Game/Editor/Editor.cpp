#include "Editor.hpp"
#include <SFML/Graphics.hpp>

SelectableObject::SelectableObject(const std::string & assetName, AssetManager & assets, const sf::Vector2f & position, const float scale):
	ScreenObject(assetName, assets, position, scale)
{}

void SelectableObject::setFollowMouse(const bool follow){
	followMouse = follow;
}

void SelectableObject::move(const sf::Vector2i & position){
	if(followMouse){
		sprite.setPosition(sf::Vector2f(position.x - sprite.getGlobalBounds().width / 2, position.y +- sprite.getGlobalBounds().height / 2));
	}
}

SelectableObject& SelectableObject::operator=(SelectableObject lhs){
	if(&lhs != this){
		followMouse = lhs.followMouse;
	}
	return *this;
}

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
				object.setFollowMouse(true);
			}
			if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
				object.setFollowMouse(false);
			}
		}
    	object.move(sf::Mouse::getPosition(window));
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