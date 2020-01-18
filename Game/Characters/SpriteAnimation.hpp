#ifndef __SPRITE_ANIMATION
#define __SPRITE_ANIMATION

#include <SFML/Graphics.hpp>
//#include "AssetManager.hpp"

class SpriteAnimation {
	private:
		sf::Sprite& sprite;
		sf::Texture& texture;
		sf::Vector2i dimensions;		// Width,height
		sf::Vector2i spriteRowColumn;	// Row, column
		sf::Vector2f scale;
		int missingRow;					// If the spritesheet is missing some frames 
		float animationSpeed;
		
		sf::Clock spriteClock;
		
		sf::IntRect rectSourceSprite;
			
		int amountColumn=0;
		int pixelRow;
		int pixelColumn;
		bool Start=false;
	
	public:
		SpriteAnimation( sf::Sprite & sprite, sf::Texture& texture, const sf::Vector2i dimensions, sf::Vector2i spriteRowColumn, sf::Vector2i scale = sf::Vector2i{1,1}, int missingRow=0, float animationSpeed = 0.1f );
		void changeStartEndFrame(  sf::Vector2i RC, sf::Vector2i missingRC, bool left);	
		void draw(sf::RenderWindow & window);

		SpriteAnimation & operator=(SpriteAnimation lhs){
			if(&lhs != this){
				sprite = lhs.sprite;
				texture = lhs.texture;
				dimensions = lhs.dimensions;
				spriteRowColumn = lhs.spriteRowColumn;
				scale = lhs.scale;
				missingRow = lhs.missingRow;
				animationSpeed = lhs.animationSpeed;
				spriteClock = lhs.spriteClock;
				rectSourceSprite = lhs.rectSourceSprite;
				amountColumn = lhs.amountColumn;
				pixelRow = lhs.pixelRow;
				pixelColumn = lhs.pixelColumn;
				Start = lhs.Start;
			}
			return *this;
		}
		
};

#endif //__SPRITE_ANIMATION