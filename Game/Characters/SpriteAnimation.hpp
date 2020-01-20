#ifndef __SPRITE_ANIMATION
#define __SPRITE_ANIMATION

#include <SFML/Graphics.hpp>
#include <iostream>

class SpriteAnimation {
	private:
		sf::Sprite& sprite;
		sf::Texture& texture;
		const sf::Vector2i dimensions;		// Width,height
		sf::Vector2i spriteRowColumn;	// Row, column
		sf::Vector2f scale;
		int missingRow;					// If the spritesheet is missing some frames 
		float animationSpeed;
		
		sf::Clock spriteClock;
		
		sf::IntRect rectSourceSprite;
			
		int specifiedColumnsHeight=0;
		int pixelRow;
		int pixelColumn;
		bool startFrameLoop=false;
	
	public:
		SpriteAnimation( sf::Sprite & sprite, sf::Texture& texture, const sf::Vector2i dimensions, sf::Vector2i spriteRowColumn, sf::Vector2i scale = sf::Vector2i{1,1}, int missingRow=0, float animationSpeed = 0.1f );
		void leftSprite(bool left);
		void changeStartEndFrame(  sf::Vector2i RC, sf::Vector2i missingRC, bool left);	
		void normalFrameLoop();
		void specifiedFrameLoop();
		void draw(sf::RenderWindow & window);

		sf::Vector2f getDimensions() const {
			return sf::Vector2f( pixelRow , pixelColumn );
		}
		
};

#endif //__SPRITE_ANIMATION