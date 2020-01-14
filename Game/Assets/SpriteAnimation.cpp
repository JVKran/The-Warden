#include "SpriteAnimation.hpp"
#include <iostream>
SpriteAnimation::SpriteAnimation( sf::Texture& texture, const sf::Vector2i dimensions, const sf::Vector2i spriteRowColumn, int missingRow ):
	texture(texture),
	dimensions(dimensions),
	spriteRowColumn(spriteRowColumn),
	missingRow(missingRow)
	//sprite.setTexture(assets.getTexture(assetName));
	//sprite.setPosition(position);
{
		
	pixelRow = dimensions.x / spriteRowColumn.x;		// Length divided by row, these are the horizontal steps a frame
	pixelColumn = dimensions.y / spriteRowColumn.y;		// Height divided by column, these are the vertical steps a frame
	rectSourceSprite = sf::IntRect( 0, 0, pixelRow, pixelColumn ); // First 2 numbers will iterate trough frames, second 2 are the width and height of a single frame
	sprite = sf::Sprite(texture, rectSourceSprite);
	//sprite.setPosition(100,100);
}

// Animate function that loops trough variying spritesheets
void SpriteAnimation::animate(){
	//Update if under 0.01 seconds;
	if(spriteClock.getElapsedTime().asSeconds() > 0.01f){
		if(rectSourceSprite.left == dimensions.x-pixelRow){ // If width is the same as width minus the horizontal steps, reset width and go 1 column down
			rectSourceSprite.left = 0;
			rectSourceSprite.top += pixelColumn;
			// If width and column are at the end of the spritesheet, start over from the beginning
		}else if(rectSourceSprite.left == dimensions.x-pixelRow*(spriteRowColumn.x-missingRow) && rectSourceSprite.top == pixelColumn*(spriteRowColumn.y-1)){ 
			rectSourceSprite.left = 0;
			rectSourceSprite.top = 0;
			// Go to the next frame
		}else{ rectSourceSprite.left += pixelRow; }
		sprite.setTextureRect(rectSourceSprite);
		spriteClock.restart();

	}
}

void SpriteAnimation::draw( sf::RenderWindow & window ){
	animate();
	window.draw(sprite);
}
/*
sf::Texture texture;
	//texture.loadFromFile("/home/hu/The-Warden/Game/Assets/Textures/PIPOYA_FREE_2D_Game_Character_Sprites/Sprite_Sheet/Enemy/Enemy001a/All/e001a_02walk.png");
	texture.loadFromFile("/home/hu/The-Warden/Game/Assets/Textures/adventurer-v1.5-Sheet.png");
	int x = 350;//2400;//350 ipv 385 vanwege lege ruimte tussen frames
	int y = 592;//2880;
	int row = 7;//5;
	int column = 16;
	int missingRow = 3;
	
	sf::Vector2i dimensions{x,y};
	sf::Vector2i spriteRowColumn{row, column};
	
	
	
	sf::IntRect rectSourceSprite(0,0,pixelRow, pixelColumn);
	sf::Sprite sprite(texture, rectSourceSprite);
	int posx = 200;
	sprite.setScale(4,4);
	
	sprite.setPosition(posx,400);
	sf::Clock spriteClock;*/

