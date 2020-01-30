/// @file

#ifndef __SPRITE_ANIMATION
#define __SPRITE_ANIMATION

#include <SFML/Graphics.hpp>
#include <iostream>
#include "AssetManager.hpp"

/// \brief
/// Sprite Animation.
/// \details
/// This class features an animated spritesheet. Used to easily create an animation
/// based on a spritesheet.
class SpriteAnimation {
	private:
		sf::Sprite& sprite;					//!< The sprite that is drawn.
		sf::Texture& texture;				//!< The used spritesheet.
		sf::Vector2i dimensions;			//!< The width and height of the spritesheet.
		sf::Vector2i spriteRowColumn;		//!< The Row and column of the spritesheet.
		sf::Vector2f scale;					//!< The scale of the sprite.
		int missingRow;						//!< If the spritesheet is missing some frames.
		float animationSpeed;				//!< The speed at which animations are played.
		sf::Vector2f hitboxscale={0.2,0.2};	//!< The hitbox.
		sf::Vector2i missingRowCollom;		//!< The missing row and collumns in a spritesheet.
		sf::Vector2i startFrame;			//!< The frame to start in.
		sf::Vector2i offset;				//!< The offset of the hitbox.
		
		sf::Clock spriteClock;				//!< The clock that determines the animation speed of the sheet.
		
		sf::IntRect rectSourceSprite;       //!< The rectangle that cuts of one frame.
			
		int specifiedColumnsHeight=0;		//!< The height of the column.
		int pixelRow;						//!< How many pixels one frame has in a row.
		int pixelColumn;					//!< How many pixels one fram has in a column
		bool startFrameLoop=false;			//!< To start the loop.
		bool ismirrored;					//!< If the sprite has to be mirrored.
	
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
		void left(bool left);
		
};

#endif //__SPRITE_ANIMATION