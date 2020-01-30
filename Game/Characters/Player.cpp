/// @file
#include <iostream>
#include "Player.hpp"

using namespace std;
using namespace cv;

/// \brief
/// Draw the Character.
/// \details
/// This function draws the Character in the RenderWindow and sets the View to the position
/// of the Character to keep the player centered.
/// @param window The RenderWindow to draw in.
/// @param position The position of the player.
/// @param view The view to follow the player.
void PlayerGraphics::processGraphics(sf::RenderWindow & window, const sf::Vector2f & position, sf::View & view){
	sprite.setPosition(position);
	if(position.y < 300){
		view.setCenter(sf::Vector2f(position.x, position.y));
	} else {
		view.setCenter(sf::Vector2f(position.x, 300));
	}
	window.draw(sprite);
}

/// \brief
/// Create an instance.
/// \details
/// This class crates an animatedPlayerGraphics instance.
/// @param assetName The name of the asset to use for retrieving the texture from the AssetManager.
/// @param assets The AssetManager to retrieve the texture from.
/// @param characterData
AnimatedPlayerGraphics::AnimatedPlayerGraphics(const std::string & assetName, AssetManager & assets, SpriteCharacter & characterData):
	AnimatedGraphicsComponent(assetName, assets, characterData)
{}

/// \brief
/// Process view changes.
/// \details
/// Sets the View to the position of the Character to keep the player centered.
void AnimatedPlayerGraphics::processViewChanges(sf::View & view, const sf::Vector2f & position){
	if(position.y < 300){
		view.setCenter(sf::Vector2f(position.x, position.y));
	} else {
		view.setCenter(sf::Vector2f(position.x, 300));
	}
}

/// \brief
/// Create an instance.
/// \details
/// This class crates a PlayerGraphics instance.
/// @param assetName The name of the asset to use for retrieving the texture from the AssetManager.
/// @param assets The AssetManager to retrieve the texture from.
PlayerGraphics::PlayerGraphics(const std::string & assetName, AssetManager & assets):
	GraphicsComponent(assetName, assets)
{}

/// \brief
/// process input.
/// \details
/// This function implements the input for players. This consists of reading basic assignable input.
/// @param position The position of the player.
/// @param direction The direction to changed based on read input.
/// @param keys The key bindings to check for key presses.
void PlayerInput::processInput(const sf::Vector2f & position, sf::Vector2f & direction, std::vector<KeyBinding> & keys){
	direction.x = 0;	//Stand still
	direction.y = 0;
	if(sf::Keyboard::isKeyPressed(keys[0].getKey())){
		direction.x = -1;
	}
	if(sf::Keyboard::isKeyPressed(keys[1].getKey())){
		direction.x = 1;
	}
	if(sf::Keyboard::isKeyPressed(keys[2].getKey())){
		direction.y = -1;
	}
}

/// \brief
/// Adds a tile in the world
/// \details
/// This is called by the game, it adds a new tile in the vector tiles in the world,
/// on the location of the mouse in the window's view (so not the normal pixel locations)
/// the new tile is a 'crate' object.
/// @param event The event to use for checking clicks.
/// @param world The world to add the tile to.
/// @param window The window to use for determining the relative position of the mouse click.
/// @param view The view to use with the window to determine the abolsute position of the mouse.
void PlayerInput::addTile(const sf::Event & event, World & world, sf::RenderWindow & window, sf::View & view){
	sf::Vector2f position = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);		//gets to position based on the mouse coordinates in a view
	sf::Vector2f teleportPosition = sf::Vector2f(0,0);
	world.addTile("crate", position, teleportPosition);
}

/// \brief
/// Adds a tile in the world
/// \details
/// This is called by the game, it adds a new tile in the world.
/// @param tile The tile we want to add in the world vector
void PlayerInput::addTile(Tile & tile){
	world.addTile(tile);
}

/// \brief
/// Deletes a tile in the world
/// \details
/// This is called by the game, and it deletes the object where the mouse is located on.
/// The mouse position is called by mapPixelToCoords which uses view to get the right location
/// and not the mouse window location.
/// @param event The event to use for checking clicks.
/// @param world The world to add the tile to.
/// @param window The window to use for determining the relative position of the mouse click.
/// @param view The view to use with the window to determine the abolsute position of the mouse.
void PlayerInput::deleteTile(const sf::Event & event, World & world, sf::RenderWindow & window, sf::View & view){
	std::vector<Tile> & tiles = world.getTiles();
	for(int_fast8_t i = tiles.size() - 1; i >= 0; i--){
		if(tiles.at(i).getBounds().contains(sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window), view)))){
			tiles.erase( std::find(tiles.begin(), tiles.end(), tiles.at(i)) );
		}
	}
}

/// \brief
/// Process item usage
/// \details
/// This function is responsible for managing and thus processing the usage of items. This can consist of using an item and/or
/// deleting an item when it's broken.
/// @param event The event to use for checking clicks.
/// @param items The items to pick one from to use.
/// @param ownCharacter The character to change the selected item for.
void PlayerInput::processItemUsage(const sf::Event & event, std::vector<std::shared_ptr<Item>> & items, Character * ownCharacter){
	if(event.type == sf::Event::MouseWheelMoved){	
		ownCharacter->getSelectedItemNumber() += event.mouseWheel.delta;
	}
	if(ownCharacter->getSelectedItemNumber()<0 ||(ownCharacter->getSelectedItemNumber()>static_cast<int_fast16_t>(items.size()-1))){
		ownCharacter->setSelectedItemNumber(0);
	} else if(event.type == sf::Event::MouseButtonReleased){
		if(event.mouseButton.button == sf::Mouse::Left){
			if(items.at(ownCharacter->getSelectedItemNumber())->use(ownCharacter, characters) && !ownCharacter->getSelectedItem()->isWeapon()){			//If item is broken
				items.erase(std::find(items.begin(), items.end(), items.at(ownCharacter->getSelectedItemNumber())));
				ownCharacter->getSelectedItemNumber()--;
			}
			if(ownCharacter->getSelectedItem()->isWeapon()){
				ownCharacter->getGraphics()->setFightAnimation(items.at(ownCharacter->getSelectedItemNumber())->getPeriod());
			}
		}
	}
}

/// \brief
/// Process input based on vision
/// \details
/// This function is used to start and detach the vision processing thread. Furthermore, it does nothing...
/// @param position The position to alter (unused).
/// @param direction The direction to change based on the processed vision input.
/// @param keys The keys to use for generating input (unused).
void InteractiveInput::processInput(const sf::Vector2f & position, sf::Vector2f & direction, std::vector<KeyBinding> & keys){
	if(!isCreated){
		std::thread inputThread(detectPosition, std::ref(direction));		//Use a cross-thread refrence to the direction.
		inputThread.detach();
		isCreated = true;
		std::cout << "(i)-- Vision detecting thread has been detached." << std::endl;
	}
}

/// \brief
/// Process input based on vision
/// \details
/// This function is used to detect the position of the face in fron of the camera. The position is used to set the direction of
/// the player. After that's done, it's up to the PhysicsComponent to determine if the wish can be fulfilled...
/// @param direction A refrence to the direction to control.
void InteractiveInput::detectPosition( sf::Vector2f & direction ){
    String face_cascade_name = "Characters/haarcascade_frontalface_alt.xml";
	cv::CascadeClassifier face_cascade;
	String window_name = "Capture - Face detection";

	cv::VideoCapture capture;
	cv::Mat frame;
	cv::Point center;

    if(!face_cascade.load( face_cascade_name )){ 
    	std::cout << "--(!)Error loading face cascade\n";
    }

	capture.open( -1 );

    if (!capture.isOpened()){ 
    	std::cout << "--(!) Error opening video capture\n";
    }

	while(capture.read(frame)){
		if( frame.empty() ){
			std::cout << " --(!) Empty frame captured!\n";
		} else {
			std::vector<Rect> faces;
		    cv::Mat frame_gray;
		    cv::cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
		    cv::equalizeHist( frame_gray, frame_gray );
		    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );
			for ( size_t i = 0; i < faces.size(); i++ ){
		        center = cv::Point( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
		        cv::ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
		        cv::Mat faceROI = frame_gray( faces[i] );
			}
		    if(center.x < 200){					//Right
		    	direction.x = 1;
		    } else if (center.x > 500){			//Left
		    	direction.x = -1;
		    } else if(center.x != 0) {			//Middle
		    	direction.x = 0;
		    }
		    if(center.y < 300){					//Jump
		    	direction.y = -1;
		    } else {
		    	direction.y = 0;				//Don't jump
		    }
		}
	}
}