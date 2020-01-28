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

		void leftSprite(bool left);
		void changeStartEndFrame(  sf::Vector2i RC, sf::Vector2i missingRC, bool left);	
		void normalFrameLoop();
		void specifiedFrameLoop();
		void draw(sf::RenderWindow & window);
		void sethitboxscale(float newscale);

		sf::Vector2f getDimensions() const;
		sf::FloatRect getBounds() const ;
		sf::FloatRect getGlobal() const ;
		void move(sf::Vector2f where);
		void left(bool where);
		
};

#endif //__SPRITE_ANIMATION