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
			return sf::Vector2f(pixelColumn *3, pixelRow *3);
			//return sf::Vector2f(sprite.getGlobalBounds().height, sprite.getGlobalBounds().width);
		}
		sf::FloatRect getBounds() const {
			//return sf::Vector2f(pixelRow * 3, pixelColumn * 3);
			sf::FloatRect temp=sprite.getGlobalBounds();
			return sf::FloatRect(sf::Vector2f(temp.left+pixelColumn*3,temp.top),sf::Vector2f(temp.width,temp.height));
			//return sprite.getGlobalBounds();
		}
		void move(sf::Vector2f where){
			sprite.setPosition(sf::Vector2f(where.x+pixelRow*1,where.y+pixelColumn*1.5));
		}
		
};

#endif //__SPRITE_ANIMATION