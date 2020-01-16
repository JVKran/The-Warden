#ifndef __SPRITE_ANIMATION
#define __SPRITE_ANIMATION

#include <SFML/Graphics.hpp>
//#include "AssetManager.hpp"

class SpriteAnimation {
	private:
		sf::Sprite& sprite;
		sf::Texture& texture;
		const sf::Vector2i dimensions;		// Width,height
		sf::Vector2i spriteRowColumn;	// Row, column
		const sf::Vector2f scale;
		int missingRow;					// If the spritesheet is missing some frames 
		float animationSpeed;
		
	
		
		sf::Clock spriteClock;
		
		sf::IntRect rectSourceSprite;
			
		int amountColumn=0;
		int pixelRow;
		int pixelColumn;
		bool Start=false;
	public:
		SpriteAnimation( sf::Sprite & sprite, sf::Texture& texture, const sf::Vector2i dimensions, sf::Vector2i spriteRowColumn, const sf::Vector2i scale = sf::Vector2i{1,1}, int missingRow=0, float animationSpeed = 0.1f );
		void changeStartEndFrame(  sf::Vector2i RC, sf::Vector2i missingRC);	
		void draw(sf::RenderWindow & window);
		
};

#endif //__SPRITE_ANIMATION