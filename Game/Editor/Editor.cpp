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
Editor::Editor( sf::RenderWindow & window, AssetManager & assets, std::vector<KeyBinding> & bindings  ):
	assets( assets ),
	world( assets ),
	window( window ),
	bindings( bindings )
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
void Editor::draw(sf::View & view){
	for(int_fast8_t windowLayer = 0; windowLayer <= 4; windowLayer++){
		world.draw( window, view, windowLayer );
	}
	drawTileBar( view );
}

/// \brief
/// Draw the tile bar.
/// \details
/// This function draws all available tiles to choose from to the passed RenderWindow.
/// @param window The window to write the editor and world to.
void Editor::drawTileBar( sf::View & view ){
	for( const Tile & object : objects ){
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
void Editor::handleInput(sf::View & view){
	bool leftMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	bool leftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    bool rightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
    bool downPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
    bool upPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);

    std::vector<Tile> & tiles = world.getTiles();

    auto leftIterator = std::find_if(tiles.begin(), tiles.end(), [this](const Tile & tile)->bool{return tile.getPosition().x > this->leftBound;});
	auto rightIterator = std::find_if(leftIterator, tiles.end(), [this](const Tile & tile)->bool{return tile.getPosition().x > this->rightBound;});

	std::for_each(
		leftIterator,
		rightIterator,
		[this, &view, &tiles](Tile & tile){
			handleTileInput(tile, this->window, view, tiles);
		}
	);

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

	for(Tile & object : objects){
		if(leftMousePressed){
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
	
	leftBound = view.getCenter().x - (view.getSize().x / 2) - 300;
	rightBound = view.getCenter().x + (view.getSize().x / 2);
}

void Editor::handleTileInput(Tile & tile, sf::RenderWindow & window, sf::View & view, std::vector<Tile> & tiles){
	if(tile.getBounds().contains(sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window), view)))){
		// if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && isFirstOneSelected(tiles)){
		// 	tile.setFollowMouse(true);
		// }
		// if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
		// 	tile.setFollowMouse(false);
		// }
		if(sf::Keyboard::isKeyPressed(bindings[4].getKey()) && tile.isFollowingMouse()){
			tiles.erase( std::find(tiles.begin(), tiles.end(), tile) );
		}
		if(sf::Keyboard::isKeyPressed(bindings[5].getKey())){
			tile.setCollidable(true);
		}
		if(sf::Keyboard::isKeyPressed(bindings[6].getKey())){
			tile.setCollidable(false);
		}
		if(sf::Keyboard::isKeyPressed(bindings[7].getKey())){
			tile.setWindowLayer(0);
		}
		if(sf::Keyboard::isKeyPressed(bindings[8].getKey())){
			tile.setWindowLayer(1);
		}
		if(sf::Keyboard::isKeyPressed(bindings[9].getKey())){
			tile.setWindowLayer(2);
		}
		if(sf::Keyboard::isKeyPressed(bindings[10].getKey())){
			tile.setWindowLayer(3);
		}
		if(sf::Keyboard::isKeyPressed(bindings[11].getKey())){
			tile.setWindowLayer(4);
		}
		if(sf::Keyboard::isKeyPressed(bindings[12].getKey())){
			tile.setInteractability(!tile.isInteractable());
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::M)){
			tile.setPassageWay(!tile.isPassageWay());
		}
		if(sf::Keyboard::isKeyPressed(bindings[13].getKey())){
			if(tile.isPassageWay()){
				tile.changeSelected(!tile.isSelected());
			}
		}
		if(sf::Keyboard::isKeyPressed(bindings[14].getKey())){
			if(tile.isSelected()){
				tile.changeTeleportPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
				tile.changeSelected(false);
			}
		}
	}
	tile.move(window.mapPixelToCoords(sf::Mouse::getPosition(window), view));
}

void Editor::handleEvent(const sf::Event & event, sf::View & view){
	if(event.type == sf::Event::MouseWheelMoved && objects[1].getPosition().x + objects[1].getBounds().width > sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window), view)).x){	
		scrollTileBar(event.mouseWheel.delta);
	}

	std::vector<Tile> & tiles = world.getTiles();

	auto leftIterator = std::find_if(tiles.begin(), tiles.end(), [this](const Tile & tile)->bool{return tile.getPosition().x > this->leftBound;});
	auto rightIterator = std::find_if(leftIterator, tiles.end(), [this](const Tile & tile)->bool{return tile.getPosition().x > this->rightBound;});

	std::for_each(
		leftIterator,
		rightIterator,
		[this, &view, &event](Tile & tile){
			handleObjectInput(tile, this->window, view, event);
		}
	);
}

void Editor::handleObjectInput(Tile & tile, sf::RenderWindow & window, sf::View & view, const sf::Event & event){
	if(tile.getBounds().contains(sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window), view)))){
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
}

/// \brief
/// Scroll tile bar
/// \details
/// This function is used to scroll through the tiles that can be placed in the world.
/// @param mouseWHeelDelta The new position of the mousewheel relative to its previous position.
void Editor::scrollTileBar( const int_fast16_t & mouseWheelDelta ){
	for( Tile & object : objects ){
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