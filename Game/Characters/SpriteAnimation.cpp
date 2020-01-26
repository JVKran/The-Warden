/// @file
#include "SpriteAnimation.hpp"
#include <iostream>
#include<exception>
#include <string>
#include "FactoryFunction.hpp"
#include "Character.hpp"

void SpriteAnimation::sethitboxscale(float newscale){
	hitboxscale.x=newscale;
	hitboxscale.y=newscale;
}

SpriteAnimation::SpriteAnimation(AssetManager &assets,sf::Sprite &sprite, std::string movename, std::string filename):
sprite(sprite),
texture(assets.getTexture(filename))
{
	std::ifstream charactersFile("Characters/characters.txt");
	if(!charactersFile){
		throw fileNotFound("Characters/characters.txt");
	}
	std::string prevstring="";
	sf::Vector2i position;
	sf::Vector2f datafloat;
	
	while (!isEmpty(charactersFile)){
		std::string currstring = "";
		charactersFile>>currstring;
		if((currstring.find("size")!= std::string::npos)){
			charactersFile>>position;
			dimensions=position;
		}
		if((currstring.find("grid")!= std::string::npos)){
			charactersFile>>position;
			spriteRowColumn= position;
		}
		if((currstring.find("action")!= std::string::npos)){
			charactersFile>>position;
		}
		if((currstring.find("scale")!= std::string::npos)){
			charactersFile>>datafloat;
			scale=datafloat;
		}
		if((currstring.find("filename")!= std::string::npos)){
			charactersFile>>currstring;
			filename=currstring;
		}
		if((currstring.find("missing")!= std::string::npos)){
			charactersFile>>position;
			missingRowCollom=position;
		}
		if((currstring.find("start")!= std::string::npos)){
			charactersFile>>position;
			startFrame=position;
		}
		if((currstring.find("offset")!= std::string::npos)){
			charactersFile>>position;
			offset=position;
		}
		if((currstring.find("speed")!= std::string::npos)){
			charactersFile>>datafloat;
			animationSpeed=datafloat.x;
		}
		if((currstring.find("hitfac")!= std::string::npos)){
			charactersFile>>datafloat;
			hitboxscale=datafloat;
		}
		if((currstring.find("ismirrored")!= std::string::npos)){
			ismirrored=true;
		}
		prevstring=currstring;
		if(currstring == movename){
	 		texture=assets.getTexture(filename);
			break;
		} 
		if((currstring.find("eind")!= std::string::npos)){
			currstring="";
			ismirrored = false;
		}
	}
	pixelRow = dimensions.x / spriteRowColumn.x;					// Length divided by row, these are the horizontal steps a frame
	pixelColumn = dimensions.y / spriteRowColumn.y;					// Height divided by column, these are the vertical steps a frame
	rectSourceSprite = sf::IntRect( 0, 0, pixelRow, pixelColumn ); 	// First 2 numbers will iterate trough frames, second 2 are the width and height of a single frame
	sprite = sf::Sprite(texture, rectSourceSprite);					// Give the sprite
	sprite.setScale(static_cast<sf::Vector2f>(scale));				// Set the scale
	sprite.setOrigin(pixelRow/2, pixelColumn/2);
	changeStartEndFrame(startFrame,missingRowCollom,1);

}




/// \brief
/// Enable left side of sprite.
/// \details
/// This function multiplies scale.x by -1 to flip the sprite.
/// @param left This decides whether the scale has to be left.
void SpriteAnimation::leftSprite(bool left){
	if(left&&scale.x>0){
		scale.x = scale.x*-1;
		sprite.setScale(scale.x,scale.y);
	}else if(!left&&scale.x<0){		
		scale.x = scale.x*-1;
		sprite.setScale(scale.x,scale.y);
	}
}

/// \brief
/// Set the specified start and end frame to loop trough.
/// \details
/// This function will set the specified start and end frame, the missingRow, the specifiedColumnsHeight and enables the specifiedFrameLoop().
/// @param rowColumn This has a row and a column, The row is on which sprite to begin. The column is on which column to begin.
/// @param missingRowColumn This has a missing row and a columnHeight, The missing row is how many sprites there are left in a row. The columnHeight is to specify if the amount of frames is longer than one row.
/// @param left This enables the leftside of a sprite.
void SpriteAnimation::changeStartEndFrame( sf::Vector2i rowColumn, sf::Vector2i missingRowColumn, bool left ){
	// std::cout<<"frameschanged   "<<rowColumn.x<<"   "<<rowColumn.y<<"  "<<missingRowColumn.x<<"  "<<missingRowColumn.y<<'\n';
	startFrameLoop = true;
	spriteRowColumn = rowColumn;
	missingRow = missingRowColumn.x; // If there are still sprites after the desired frames, assign them as missing(+1 for a missing frame)
	specifiedColumnsHeight = missingRowColumn.y; 
	leftSprite(left);
	//Specify start frame
	rectSourceSprite = sf::IntRect( pixelRow*spriteRowColumn.x, pixelColumn*spriteRowColumn.y, pixelRow, pixelColumn );

}

/// \brief
/// This loops trough the entire spritesheet.
/// \details
/// This function will go from frame to frame and goes back to the beginning when it reaches the end.
void SpriteAnimation::normalFrameLoop(){
	if(rectSourceSprite.left == dimensions.x-pixelRow){  		// If you're at the end of the row, begin at he first row and go one column down	
		rectSourceSprite.left = 0;								// 
		rectSourceSprite.top += pixelColumn; 		 			// Go one column down	
			// If width and column are at the end of the spritesheet, start over from the beginning
	}else if( rectSourceSprite.left == dimensions.x-pixelRow*(spriteRowColumn.x-missingRow) && rectSourceSprite.top == pixelColumn*(spriteRowColumn.y -1)){ 	
		rectSourceSprite.left = 0;	 							// Go back to the specified start frame
		rectSourceSprite.top = 0; 								// Go back to the specified start frame
		// Go to the next frame
	}else{ 
		rectSourceSprite.left += pixelRow;
	}
}

/// \brief
/// This loops trough the specified parts of the spritesheet.
/// \details
/// This function will start from the specified frame to the specified end frame and goes back to the specified start frame when it reaches the end.
void SpriteAnimation::specifiedFrameLoop(){
	if(rectSourceSprite.left == dimensions.x-pixelRow){ 		// If you're at the end of the row, begin at he first row and go one column down	
		rectSourceSprite.left = 0;
		rectSourceSprite.top += pixelColumn; 					// Go one column down
	}else{ 
		rectSourceSprite.left += pixelRow;
	}
	if( ( rectSourceSprite.left == dimensions.x-pixelRow*missingRow ||rectSourceSprite.left == dimensions.x-pixelRow ) && rectSourceSprite.top == pixelColumn*(spriteRowColumn.y+specifiedColumnsHeight) ){
		rectSourceSprite.left = pixelRow * spriteRowColumn.x; 	// Go back to the specified start frame
		rectSourceSprite.top = pixelColumn * spriteRowColumn.y; // Go back to the specified start frame
	}
}

/// \brief
/// This draws the sprite.
/// \details
/// This function will draw the sprite.
/// @param window The RenderWindow to draw the sprite in.
void SpriteAnimation::draw( sf::RenderWindow & window ){
	if(spriteClock.getElapsedTime().asSeconds() > animationSpeed){
		if(!startFrameLoop){
			normalFrameLoop();
		}else{ 
			specifiedFrameLoop(); 
		}	
		sprite.setTextureRect(rectSourceSprite); 				// Set the texture of the sprite to the next frame.
		spriteClock.restart();
	}
	window.draw(sprite);
	
}

sf::Vector2f SpriteAnimation::getDimensions() const {
	return sf::Vector2f(pixelColumn*hitboxscale.x, pixelRow*hitboxscale.y);
}

sf::FloatRect SpriteAnimation::getBounds() const {
	sf::FloatRect temp=sprite.getGlobalBounds();
	return sf::FloatRect(sf::Vector2f(temp.left+pixelRow*hitboxscale.x,temp.top+pixelColumn*hitboxscale.y),sf::Vector2f(temp.width,temp.height));
}

void SpriteAnimation::move(sf::Vector2f where){
	sprite.setPosition(sf::Vector2f(where.x+pixelRow*0.5*hitboxscale.x+offset.x,where.y-pixelColumn*0.5*hitboxscale.y+offset.y));
}

void SpriteAnimation::left(bool where){
	changeStartEndFrame(startFrame,missingRowCollom,where!=ismirrored);
}

