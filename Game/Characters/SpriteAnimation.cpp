/// @file
#include "SpriteAnimation.hpp"
#include <iostream>

/// \brief
/// Create instance.
/// \details
/// This function creates a SpriteAnimation.
/// @param sprite This is the sprite.
/// @param texture This has the spritesheet as texture for the sprite.
/// @param dimensions This has the width(dimension.x) and height(dimension.y) of the spritesheet.
/// @param spriteRowColumn This has the amount of horizontal sprites(row) and the amount of vertical sprites(column).
/// @param scale This has the scale the sprite has to be.
/// @param missingRow This is how many sprites are missing at the end.
/// @param animationSpeed This is the animationSpeed.
SpriteAnimation::SpriteAnimation( sf::Sprite& sprite, sf::Texture& texture, const sf::Vector2i dimensions, sf::Vector2i spriteRowColumn, 
								  sf::Vector2i scale, int missingRow,  float animationSpeed ):
	sprite(sprite),	
	texture(texture),
	dimensions(dimensions),
	spriteRowColumn(spriteRowColumn),
	scale(scale),
	missingRow(missingRow),
	animationSpeed(animationSpeed)
	

{	
	pixelRow = dimensions.x / spriteRowColumn.x;					// Length divided by row, these are the horizontal steps a frame
	pixelColumn = dimensions.y / spriteRowColumn.y;					// Height divided by column, these are the vertical steps a frame
	rectSourceSprite = sf::IntRect( 0, 0, pixelRow, pixelColumn ); 	// First 2 numbers will iterate trough frames, second 2 are the width and height of a single frame
	sprite = sf::Sprite(texture, rectSourceSprite);					// Give the sprite
	sprite.setScale(static_cast<sf::Vector2f>(scale));				// Set the scale
	sprite.setOrigin(pixelRow/2, pixelColumn/2);						// Set the origin to the middle
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
