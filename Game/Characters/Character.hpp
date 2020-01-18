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

		PlayerPhysics & operator=(PlayerPhysics lhs){
			if(&lhs != this){
				previous = lhs.previous;
				jumpTime = lhs.jumpTime;
				current = lhs.current;
				elapsed = lhs.elapsed;
				state = lhs.state;
			}
			return *this;
		}
};

class PlayerInput : public InputComponent {
	public:
		virtual void processInput(sf::Vector2f & velocity);
};

class GraphicsComponent {
	private:
		sf::Sprite sprite;
		SpriteAnimation Animation;

		std::vector<sf::Vector2i> spriteCharacterData{sf::Vector2i{350,592},sf::Vector2i{7,16}, sf::Vector2i{5,5}, sf::Vector2i{3,0}};
		std::vector<sf::Vector2i> spriteCharacterAction{ sf::Vector2i{0,0}, sf::Vector2i{3,0}, sf::Vector2i{3,3}, sf::Vector2i{0,0}, sf::Vector2i{1,1},sf::Vector2i{0,0}, sf::Vector2i{2,2}, sf::Vector2i{6,1}};
		std::vector<std::string> spriteCharacterNames{"idle","slide", "walk", "jump"};

		std::map<std::string, std::vector<sf::Vector2i> > animation;
		std::string lastAnimation;
	public:
		GraphicsComponent(const std::string & assetName, AssetManager & assets):
						Animation(sprite, assets.getTexture(assetName), spriteCharacterData[0], spriteCharacterData[1], spriteCharacterData[2], spriteCharacterData[3].x)
					{	
			
			// Fill map with actions
			for( unsigned int i=0; i<spriteCharacterNames.size();i++){
				animation[spriteCharacterNames[i]] = std::vector<sf::Vector2i> {spriteCharacterAction[i+i], spriteCharacterAction[i+i+1]};
			}
			// Start animation to idle
			Animation.changeStartEndFrame( animation["idle"][0], animation["idle"][1], 0);
			
			}

		void processGraphics(sf::RenderWindow & window, const sf::Vector2f & position, std::string name, bool leftSprite) ;
		sf::Vector2f getDimensions();

		GraphicsComponent & operator=(GraphicsComponent lhs){
			if(&lhs != this){
				sprite = lhs.sprite;
				Animation = lhs.Animation;
				animation = lhs.animation;
				lastAnimation = lhs.lastAnimation;
			}
			return *this;
		}
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
		Character(const sf::Vector2f & position, const std::string & assetName, AssetManager & assets, sf::RenderWindow &window);
		
		void update(sf::RenderWindow & window, World & world, const std::string & action, bool leftSprite);
		void attack();
		void draw();

		Character & operator=(Character lhs){
			if(&lhs != this){
				position = lhs.position;
				velocity = lhs.velocity;
				physics = lhs.physics;
				graphics = lhs.graphics;
			}
			return *this;
		}

};

#endif //__CHARACTER_HPP