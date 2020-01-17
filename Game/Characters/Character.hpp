#ifndef __CHARACTER_HPP
#define __CHARACTER_HPP

#include <SFML/Graphics.hpp>
#include "World.hpp"
#include "SpriteAnimation.hpp"

class PhysicsComponent {
	public:
		virtual void processPhysics(World & world, sf::Vector2f & position, sf::Vector2f velocity, const sf::Vector2f & dimensions) = 0;
};

class InputComponent {
	public:
		virtual void processInput(sf::Vector2f & velocity) = 0;
};
class PlayerPhysics : public PhysicsComponent {
	private:
	    double previous, jumpTime, current, elapsed;
		sf::Clock clock;
		enum class states { JUMPING, STANDING, CROUCHING, FALLING};
		states state = states::FALLING;
	public:
		virtual void processPhysics(World & world, sf::Vector2f & position, sf::Vector2f velocity, const sf::Vector2f & dimensions);
};

class PlayerInput : public InputComponent {
	public:
		virtual void processInput(sf::Vector2f & velocity);
};

class GraphicsComponent {
	private:
		sf::Sprite sprite;
		SpriteAnimation Animation;

		std::map<std::string, std::vector<sf::Vector2i> > animation;
		std::string lastAnimation;
	public:
		GraphicsComponent(const std::string & assetName, 
						AssetManager & assets, 
						const std::vector<sf::Vector2i>  & spriteCharacterData, 
					  	const std::vector<sf::Vector2i> & spriteCharacterAction, 
					   	const std::vector<std::string> & spriteCharacterNames
					):
						Animation(sprite, assets.getTexture(assetName), spriteCharacterData[0], spriteCharacterData[1], spriteCharacterData[2], spriteCharacterData[3].x)
					{	
			
			// Fill map with actions
			for( unsigned int i=0; i<spriteCharacterNames.size();i++){
				animation[spriteCharacterNames[i]] = std::vector<sf::Vector2i> {spriteCharacterAction[i+i], spriteCharacterAction[i+i+1]};
			}
			// Start animation to idle
			//Animation.changeStartEndFrame( animation["idle"][0], animation["idle"][1], 0);
			
			}

		void processGraphics(sf::RenderWindow & window, const sf::Vector2f & position, std::string name, bool leftSprite) ;
		sf::Vector2f getDimensions();
};

class Character {
	private:

		sf::Vector2f position;
		sf::Vector2f velocity;
		sf::RenderWindow &window;
		//std::string action="jump";
		
		PlayerInput input;
		PlayerPhysics physics;
		GraphicsComponent graphics;
	public:
		Character(const sf::Vector2f & position, const std::string & assetName, AssetManager & assets, sf::RenderWindow &window,
				  const std::vector<sf::Vector2i>  &spriteCharacterData, const std::vector<sf::Vector2i>  &spriteCharacterAction, 
				  const std::vector<std::string> & spriteCharacterNames);
		
		void update(sf::RenderWindow & window, World & world, const std::string & action, bool leftSprite);
		void attack();
		void draw();

};

#endif //__CHARACTER_HPP