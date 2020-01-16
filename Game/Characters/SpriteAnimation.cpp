#include "SpriteAnimation.hpp"
#include <iostream>
SpriteAnimation::SpriteAnimation( sf::Sprite& sprite, sf::Texture& texture, const sf::Vector2i dimensions, sf::Vector2i spriteRowColumn, 
								 const sf::Vector2i scale, int missingRow,  float animationSpeed ):
	sprite(sprite),	
	texture(texture),
	dimensions(dimensions),
	spriteRowColumn(spriteRowColumn),
	scale(scale),
	missingRow(missingRow),
	animationSpeed(animationSpeed)
	

{
	pixelRow = dimensions.x / spriteRowColumn.x;		// Length divided by row, these are the horizontal steps a frame
	pixelColumn = dimensions.y / spriteRowColumn.y;		// Height divided by column, these are the vertical steps a frame
	rectSourceSprite = sf::IntRect( 0, 0, pixelRow, pixelColumn ); // First 2 numbers will iterate trough frames, second 2 are the width and height of a single frame
	sprite = sf::Sprite(texture, rectSourceSprite);
	sprite.setScale(static_cast<sf::Vector2f>(scale));
}


// Animate function that loops trough variying spritesheets
// start = Enable if statement
// startRow = Which frame in a row to start
// startColumn = Which column to start
// missRow =  If there are still sprites after the desired frames, assign them as missing(+1 for a missing frame
// Column = How tall the column has to be
void SpriteAnimation::changeStartEndFrame( sf::Vector2i RC, sf::Vector2i missingRC ){
	//std::cout<<"init\n";
	Start = true;
	spriteRowColumn = RC;
	missingRow = missingRC.x; // If there are still sprites after the desired frames, assign them as missing(+1 for a missing frame)
	amountColumn = missingRC.y; 
	//Specify start frame
	rectSourceSprite = sf::IntRect( pixelRow*spriteRowColumn.x, pixelColumn*spriteRowColumn.y, pixelRow, pixelColumn );
}

void SpriteAnimation::draw( sf::RenderWindow & window ){
	if(spriteClock.getElapsedTime().asSeconds() > animationSpeed){
		if(rectSourceSprite.left == dimensions.x-pixelRow){ // If you're at the end of the row, begin at he first row and go one column down
			
			rectSourceSprite.left = 0;
			rectSourceSprite.top += pixelColumn; // plek naar beneden
			
			// If width and column are at the end of the spritesheet, start over from the beginning
		}else if( !Start && rectSourceSprite.left == dimensions.x-pixelRow*(spriteRowColumn.x-missingRow) && rectSourceSprite.top == pixelColumn*(spriteRowColumn.y -1)){ 
			
			rectSourceSprite.left = 0;	 //terug naar startpositie
			rectSourceSprite.top = 0; 	 // terug naar startpositie
			
			// Go to the next frame
		}else{ rectSourceSprite.left += pixelRow;

 }
		
		// This will loop trough the specified frames
		if( Start && ( rectSourceSprite.left == dimensions.x-pixelRow*missingRow ||rectSourceSprite.left == dimensions.x-pixelRow ) 
		   && rectSourceSprite.top == pixelColumn*(spriteRowColumn.y+amountColumn) ){


			rectSourceSprite.left = pixelRow*spriteRowColumn.x; 	//terug naar startpositie van loop
			rectSourceSprite.top = pixelColumn * spriteRowColumn.y; // terug naar startpositie van loop
			
		}
		
		//std::cout << rectSourceSprite.left << " : " << rectSourceSprite.top << "\n";
		sprite.setTextureRect(rectSourceSprite);
		spriteClock.restart();
	}
	window.draw(sprite);
}

