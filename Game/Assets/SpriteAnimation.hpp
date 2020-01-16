#ifndef __SPRITE_ANIMATION
#define __SPRITE_ANIMATION

#include <SFML/Graphics.hpp>
//#include "AssetManager.hpp"

class SpriteAnimation {
	private:
		sf::Texture& texture;
		const sf::Vector2i dimensions;		// Width,height
		sf::Vector2i spriteRowColumn;	// Row, column
		int missingRow;					// If the spritesheet is missing some frames 
		float animationSpeed;
		const sf::Vector2f scale;
	
		sf::Sprite sprite;
		sf::Clock spriteClock;
		
		sf::IntRect rectSourceSprite;
			
		int amountColumn=0;
		int pixelRow;
		int pixelColumn;
		bool Start=false;
	public:
		SpriteAnimation( sf::Texture& texture, const sf::Vector2i dimensions, sf::Vector2i spriteRowColumn, int missingRow, float animationSpeed = 0.1f, const sf::Vector2f scale = sf::Vector2f{1,1} );
		void changeStartEndFrame( int startRow, int startColumn, int missingRow, int Column);	
		void draw(sf::RenderWindow & window);
		
};

#endif //__SPRITE_ANIMATION