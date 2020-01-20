/// @file

#include "Editor.hpp"
#include "FactoryFunction.hpp"
#include <SFML/Graphics.hpp>

/// \brief
/// Create an instance.
/// \details
/// This creates an Editor. In the background, World loads and initializes itself. Furhtermore the view
/// and assets are assigned and the objects available in the editor are loaded.
/// @param assets The AssetManager to use to retrieve assets.
/// @param worldFileName The filename of the world to edit. Can be both a new and existing file.
/// @param view The view to use for scrolling through the world.
Editor::Editor( AssetManager & assets ):
	assets( assets ),
	world( assets )
{
	loadObjects();
}

/// \brief
/// Save world to configuration file.
/// \details
/// This function currently saves the edited world.
void Editor::editingDone(){
	world.saveWorld();
}

/// \brief
/// Draw the editor and world.
/// \details
/// This function draws both, the editor and world to the passed RenderWindow.
/// @param window The window to write the editor and world to.
void Editor::draw(sf::RenderWindow & window, sf::View & view){
	for(int_fast8_t windowLayer = 0; windowLayer < 3; windowLayer++){
		world.draw( window, view, windowLayer );
	}
	drawTileBar( window, view );
}

/// \brief
/// Draw the tile bar.
/// \details
/// This function draws all available tiles to choose from to the passed RenderWindow.
/// @param window The window to write the editor and world to.
void Editor::drawTileBar( sf::RenderWindow & window, sf::View & view ){
	for( const auto & object : objects ){
		if(object.getPosition().x + 100 > view.getCenter().x-view.getSize().x && object.getPosition().x - 100 < view.getCenter().x+view.getSize().x){
			object.draw(window);
			//std::cout << tile.getPosition().x << std::endl;
		}
	}
}

/// \brief
/// Handle user input.
/// \details
/// This function is used to select clicked objects, move clicked objects to the world and store placed objects in the world.
/// Furthermore, the scrolling of a mouse wheel is delegated to scrollTileBar().
/// @param window The window to use for determining the absolute position of the mouseclicks.
void Editor::handleInput(sf::RenderWindow & window, sf::Event & event, sf::View & view){
	bool leftMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	bool rightMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Right);
	bool leftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    bool rightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
    bool downPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
    bool upPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);

    std::vector<Tile> & tiles = world.getTiles();
    for(auto & tile : tiles){
    	if(tile.getBounds().contains(sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window), view)))){
			// if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && isFirstOneSelected(tiles)){
			// 	tile.setFollowMouse(true);
			// }
			// if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
			// 	tile.setFollowMouse(false);
			// }
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Delete) && tile.isFollowingMouse()){
				tiles.erase( std::find(tiles.begin(), tiles.end(), tile) );
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::LBracket)){
				tile.setCollidable(true);
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::RBracket)){
				tile.setCollidable(false);
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::F1)){
				tile.setWindowLayer(0);
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::F2)){
				tile.setWindowLayer(1);
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::F3)){
				tile.setWindowLayer(2);
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::F4)){
				tile.setWindowLayer(3);
			}
			if(event.type == sf::Event::MouseWheelMoved){
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)){
					tile.setRotation(tile.getRotation() + event.mouseWheel.delta);
				} else {
					tile.setNewScale(tile.getScale().x + (event.mouseWheel.delta * 0.1));
				}
			}
			if(event.type == sf::Event::MouseButtonPressed){
				tile.setFollowMouse(true);
			}
			if(event.type == sf::Event::MouseButtonReleased){
				tile.setFollowMouse(false);
			}
		}
    	tile.move(window.mapPixelToCoords(sf::Mouse::getPosition(window), view));
    }


    if(leftPressed){
		view.setCenter(sf::Vector2f(view.getCenter().x - 3, view.getCenter().y));
	}
	if(rightPressed){
		view.setCenter(sf::Vector2f(view.getCenter().x + 3, view.getCenter().y));
	}
	if(upPressed){
		view.setCenter(sf::Vector2f(view.getCenter().x , view.getCenter().y + 3));
    }
    if(downPressed) {
    	view.setCenter(sf::Vector2f(view.getCenter().x , view.getCenter().y - 3));
    }

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
		editingDone();
	}
	if(event.type == sf::Event::MouseWheelMoved && objects[1].getPosition().x + objects[1].getBounds().width > sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window), view)).x){	
		scrollTileBar(event.mouseWheel.delta);
	}

	for(auto & object : objects){
		if(leftMousePressed || rightMousePressed){
			if(object.getBounds().contains(sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window), view)))){
				if(!object.isPartOfWorld()){
					std::cout << "Added object at position " << object.getPosition().x << std::endl;
					Tile objectToAdd = object;
					objectToAdd.setNewScale(1);
					objectToAdd.setFollowMouse(true);
					objectToAdd.setWindowLayer(1);
					world.addTile(objectToAdd);
					object.makePartOfWorld(true);
				}
			} else {
				object.makePartOfWorld(false);
			}
		}
		if(rightPressed){
    		object.setPosition(sf::Vector2f(object.getPosition().x + 3, object.getPosition().y));
	    }
	    if(leftPressed) {
	    	object.setPosition(sf::Vector2f(object.getPosition().x - 3, object.getPosition().y));
	    }
	    if(upPressed){
			object.setPosition(sf::Vector2f(object.getPosition().x, object.getPosition().y + 3));
	    }
	    if(downPressed) {
	    	object.setPosition(sf::Vector2f(object.getPosition().x, object.getPosition().y - 3));
	    }
	}
}

/// \brief
/// Scroll tile bar
/// \details
/// This function is used to scroll through the tiles that can be placed in the world.
/// @param mouseWHeelDelta The new position of the mousewheel relative to its previous position.
void Editor::scrollTileBar( const int_fast16_t & mouseWheelDelta ){
	for( auto & object : objects ){
		sf::Vector2f position = object.getPosition();
		position.y += mouseWheelDelta * 30;
		object.setPosition(position);
	}
}

/// \brief
/// Load all placeable objects.
/// \details
/// This function is used to load all selectable objects from the editorConfigName into a vector of type Tile.
/// This editor configuration file should follow a specific syntax like below:
/// ~~~~~{.txt}
///	tree1 0.5
/// tree2 0.2
/// grass 0.4
/// ~~~~~
/// In this configuration file, every line consists of an assetName and a scale to use in the editor; not the scale in the world.
/// That one is given in the world configuration file.
/// @param window The window to use for determining the absolute position of the mouseclicks.
void Editor::loadObjects(const std::string & editorConfigName ){
	std::ifstream objectInput(editorConfigName);
	std::string name;
	float scale;
	sf::Vector2f position { 10, 10 };
	while( !isEmpty( objectInput ) ){
		objectInput >> name >> scale;
		objects.push_back(Tile(name, assets, position, scale));
		position.y += 70;
	}
}	

void Editor::selectWorld(const std::string & worldName){
	world.loadWorld(worldName);
}

/// \brief
/// First one selected?
/// \details
/// This function returns wether or not there are any objects that are selected. This is used
/// to prevent selecting a tile over which the cursor is moved while moving a selected object.
/// @param tiles The vector of tiles that has to be searched for selected objects.
bool Editor::isFirstOneSelected(std::vector<Tile> & tiles){
	for(const auto & tile : tiles){
		if(tile.isFollowingMouse()){
			return false;
		}
	}
	return true;
}