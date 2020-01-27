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
	if(sf::Keyboard::isKeyPressed(keys[3].getKey())){

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
	world.addTile("crate", position);
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

/// This class implements the input for players. This consists of reading basic assignable input, item selection and item usage.
void PlayerInput::processItemUsage(std::vector<std::shared_ptr<Item>> & items, Character * ownCharacter){
	if(ownCharacter->getSelectedItemNumber()<0 ||(ownCharacter->getSelectedItemNumber()>static_cast<int_fast16_t>(items.size()-1))){
		ownCharacter->setSelectedItemNumber(0);
		return;
	}
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){			
		if(items.at(ownCharacter->getSelectedItemNumber())->use(ownCharacter, characters) && !ownCharacter->getSelectedItem()->isWeapon()){			//If item is broken
			items.erase(std::find(items.begin(), items.end(), items.at(ownCharacter->getSelectedItemNumber())));
			ownCharacter->getSelectedItemNumber()--;
		}
		if(ownCharacter->getSelectedItem()->isWeapon()){
			ownCharacter->getGraphics()->setFightAnimation(items.at(ownCharacter->getSelectedItemNumber())->getPeriod());
		}
	}
}

void PlayerInput::handleEvent(const sf::Event & event, int_fast16_t & selectedItem){
	if(event.type == sf::Event::MouseWheelMoved){	
		selectedItem += event.mouseWheel.delta;
	}
}

void PlayerInput::handleInteraction(World & world){
	std::vector<Tile> & tiles = world.getTiles();
	for(int_fast8_t i = tiles.size() - 1; i >= 0; i--){
		if(tiles.at(i).isInteractable()){
			if(tiles.at(i).isPassageWay()){
				std::cout<<"Deur\n";
			}
		}
	}
}

void InteractiveInput::detectPosition( sf::Vector2f & direction ){
    String face_cascade_name = "Characters/haarcascade_frontalface_alt.xml";
	String eyes_cascade_name = "Characters/haarcascade_eye_tree_eyeglasses.xml";
	CascadeClassifier face_cascade;
	CascadeClassifier eyes_cascade;
	String window_name = "Capture - Face detection";

	VideoCapture capture;
	Mat frame;
    //-- Detect faces
    int xPoint;
    int yPoint;

    if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading face cascade\n");};
    if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading eyes cascade\n");};
    //-- 2. Read the video stream
    capture.open( -1 );
    if ( ! capture.isOpened() ) { printf("--(!)Error opening video capture\n");}

	while(capture.read(frame)){
		if( frame.empty() ){
			printf(" --(!) No captured frame -- Break!");
		} else {
			std::vector<Rect> faces;
		    Mat frame_gray;
		    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
		    equalizeHist( frame_gray, frame_gray );
		    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );
			for ( size_t i = 0; i < faces.size(); i++ ){
		        Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
		        xPoint = center.x;
		        yPoint = center.y;
		        ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
		        Mat faceROI = frame_gray( faces[i] );
		        std::vector<Rect> eyes;
		        //-- In each face, detect eyes
		        // eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CASCADE_SCALE_IMAGE, Size(30, 30) );
		        // for ( size_t j = 0; j < eyes.size(); j++ )
		        // {
		        //     Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
		        //     int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
		        //     circle( frame, eye_center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
		        // }
			}
		    if(xPoint < 200){
		    	std::cout << 'r' << std::endl;
		    	direction.x = 1;
		    } else if (xPoint > 500){
		    	std::cout << 'l' << std::endl;
		    	direction.x = -1;
		    } else if(xPoint != 0) {
		    	std::cout << 'm' << std::endl;
		    	direction.x = 0;
		    } else {
		    	std::cout << "Fail" << std::endl;
		    }
		    if(yPoint < 300){
		    	direction.y = -1;
		    	std::cout << "Jump" << std::endl;
		    } else {
		    	direction.y = 0;
		    }
		}
	}
}