#ifndef __SPRITE_ANIMATION
#define __SPRITE_ANIMATION

#include <SFML/Graphics.hpp>
//#include "AssetManager.hpp"

class SpriteAnimation {
	private:
		sf::Texture& texture;
		const sf::Vector2i dimensions;		// Width,height
		const sf::Vector2i spriteRowColumn;	// Row, column
		int missingRow;						// If the spritesheet is missin some frames 
		
		sf::Sprite sprite;
		sf::Clock spriteClock;
		
		sf::IntRect rectSourceSprite;
	
		int pixelRow;
		int pixelColumn;
	public:
		SpriteAnimation( sf::Texture& texture, const sf::Vector2i dimensions, const sf::Vector2i spriteRowColumn,  int missingRow );
		void animate();
		void draw(sf::RenderWindow & window);
		
};

#endif //__SPRITE_ANIMATION