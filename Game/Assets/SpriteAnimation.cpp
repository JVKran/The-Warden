#include "SpriteAnimation.hpp"
#include <iostream>
SpriteAnimation::SpriteAnimation( sf::Texture& texture, const sf::Vector2i dimensions,sf::Vector2i spriteRowColumn, int missingRow, const sf::Vector2f scale):
	texture(texture),
	dimensions(dimensions),
	spriteRowColumn(spriteRowColumn),
	missingRow(missingRow),
	scale(scale)
	//sprite.setTexture(assets.getTexture(assetName));
	//sprite.setPosition(position);
{
		
	pixelRow = dimensions.x / spriteRowColumn.x;		// Length divided by row, these are the horizontal steps a frame
	pixelColumn = dimensions.y / spriteRowColumn.y;		// Height divided by column, these are the vertical steps a frame
	rectSourceSprite = sf::IntRect( 0, 0, pixelRow, pixelColumn ); // First 2 numbers will iterate trough frames, second 2 are the width and height of a single frame
	sprite = sf::Sprite(texture, rectSourceSprite);
	sprite.setScale(scale);
	//sprite.setPosition(100,100);
}

// Animate function that loops trough variying spritesheets
void SpriteAnimation::changeStartFrame( int newRow, int newColumn, int newMissing){
	
	spriteRowColumn = sf::Vector2i{ newRow, newColumn};
	missingRow = newMissing; // If there are still sprites after the desired frames, assign them as missing(+1 missing a frame)
	rectSourceSprite = sf::IntRect( pixelRow*spriteRowColumn.x, pixelColumn*spriteRowColumn.y, pixelRow, pixelColumn );
}
//velocity = sprite, pos, att
void SpriteAnimation::draw( sf::RenderWindow & window ){
	if(spriteClock.getElapsedTime().asSeconds() > 0.05f){
		if(rectSourceSprite.left == dimensions.x-pixelRow){ // If width is the same as width minus the horizontal steps, reset width and go 1 column down
			rectSourceSprite.left = dimensions.x-pixelRow*spriteRowColumn.x;
			rectSourceSprite.top += pixelColumn;
			// If width and column are at the end of the spritesheet, start over from the beginning
		}else if(rectSourceSprite.left == dimensions.x-pixelRow*(spriteRowColumn.x-missingRow) && rectSourceSprite.top == pixelColumn*(spriteRowColumn.y-1)){ 
			rectSourceSprite.left = dimensions.x-pixelRow*spriteRowColumn.x;
			rectSourceSprite.top = dimensions.y-pixelColumn*spriteRowColumn.y;
			// Go to the next frame
		}else{ rectSourceSprite.left += pixelRow; }
		sprite.setTextureRect(rectSourceSprite);
		spriteClock.restart();
		
	}
	window.draw(sprite);
}

