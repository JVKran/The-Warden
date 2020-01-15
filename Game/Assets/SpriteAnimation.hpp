#ifndef __SPRITE_ANIMATION
#define __SPRITE_ANIMATION

#include <SFML/Graphics.hpp>
//#include "AssetManager.hpp"

class SpriteAnimation {
	private:
		sf::Texture& texture;
		const sf::Vector2i dimensions;		// Width,height
		sf::Vector2i spriteRowColumn;	// Row, column
		int missingRow;						// If the spritesheet is missing some frames 
		const sf::Vector2f scale;
	
		sf::Sprite sprite;
		sf::Clock spriteClock;
		
		sf::IntRect rectSourceSprite;
	
		int pixelRow;
		int pixelColumn;
	public:
		SpriteAnimation( sf::Texture& texture, const sf::Vector2i dimensions, sf::Vector2i spriteRowColumn,int missingRow,  const sf::Vector2f scale = sf::Vector2f{1,1} );
		void changeStartFrame( int newRow, int newColumn, int newMissing);	
		void draw(sf::RenderWindow & window);
		
};

#endif //__SPRITE_ANIMATION