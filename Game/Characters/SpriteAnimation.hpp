#ifndef __SPRITE_ANIMATION
#define __SPRITE_ANIMATION

#include <SFML/Graphics.hpp>
#include <iostream>
#include "AssetManager.hpp"

class SpriteAnimation {
	private:
		sf::Sprite& sprite;
		sf::Texture& texture;
		sf::Vector2i dimensions;		// Width,height
		sf::Vector2i spriteRowColumn;	// Row, column
		sf::Vector2f scale;
		int missingRow;					// If the spritesheet is missing some frames 
		float animationSpeed;
		sf::Vector2f hitboxscale={0.2,0.2};
		sf::Vector2i missingRowCollom;
		sf::Vector2i startFrame;
		sf::Vector2i offset;
		
		sf::Clock spriteClock;
		
		sf::IntRect rectSourceSprite;
			
		int specifiedColumnsHeight=0;
		int pixelRow;
		int pixelColumn;
		bool startFrameLoop=false;
		bool ismirrored;
	
	public:
		SpriteAnimation(AssetManager &assets,sf::Sprite& sprite, std::string movename, std::string filename);
		SpriteAnimation( sf::Sprite & sprite, sf::Texture& texture, const sf::Vector2i dimensions, sf::Vector2i spriteRowColumn, sf::Vector2i scale = sf::Vector2i{5,5}, sf::Vector2i missingRowCollom = sf::Vector2i{0,0}, sf::Vector2i startpos=sf::Vector2i{0,0}, float animationSpeed = 0.1f );
		void leftSprite(bool left);
		void changeStartEndFrame(  sf::Vector2i RC, sf::Vector2i missingRC, bool left);	
		void normalFrameLoop();
		void specifiedFrameLoop();
		void draw(sf::RenderWindow & window);
		void sethitboxscale(float newscale);

		sf::Vector2f getDimensions() const {
			return sf::Vector2f(pixelColumn*hitboxscale.x, pixelRow*hitboxscale.y);
			//return sf::Vector2f(sprite.getGlobalBounds().height, sprite.getGlobalBounds().width);
		}
		sf::FloatRect getBounds() const {
			//return sf::Vector2f(pixelRow * 3, pixelColumn * 3);
			sf::FloatRect temp=sprite.getGlobalBounds();


			return sf::FloatRect(sf::Vector2f(temp.left+pixelRow*hitboxscale.x,temp.top+pixelColumn*hitboxscale.y),sf::Vector2f(temp.width,temp.height));
			//return sprite.getGlobalBounds();
		}
		void move(sf::Vector2f where){
			// std::cout<<"schaal"<<hitboxscale<<'\n';
			sprite.setPosition(sf::Vector2f(where.x+pixelRow*0.5*hitboxscale.x+offset.x,where.y-pixelColumn*0.5*hitboxscale.y+offset.y));
		}
		void left(bool where){
			// std::cout<<"schaal"<<hitboxscale<<'\n';
		changeStartEndFrame(startFrame,missingRowCollom,where!=ismirrored);
		}
		
};

#endif //__SPRITE_ANIMATION