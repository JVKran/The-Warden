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

class GraphicsComponent {
		SpriteAnimation( sf::Texture& texture, const sf::Vector2i dimensions, sf::Vector2i spriteRowColumn, 
						int missingRow, float animationSpeed = 0.1f, const sf::Vector2f scale = sf::Vector2f{1,1} );	
	protected:
		std::map<std::string, SpriteAnimation> animation;
		sf::Sprite sprite;
	public:
		GraphicsComponent(const std::string & assetName, AssetManager & assets, std::vector){
			
			SpriteAnimation Animation(sprite&, assets.getTexture(assetName), sf::Vector2i dimensions, 
									  sf::Vector2i spriteRowColumn, int missingRow)
			
			animation[actionName] = Animation;
			
			//sprite.setTexture(assets.getTexture(assetName));
		}

		virtual void processGraphics(sf::RenderWindow & window, const sf::Vector2f & position, const std::string name) = 0;
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

class PlayerGraphics : public GraphicsComponent {
	public:
		PlayerGraphics(const std::string & assetName, AssetManager & assets):
			GraphicsComponent(assetName, assets)
		{}

		virtual void processGraphics(sf::RenderWindow & window, const sf::Vector2f & position, const std::string name) override;
		sf::Vector2f getDimensions();
};

class Character {
	private:
		sf::Vector2f position;
		sf::Vector2f velocity;
		sf::RenderWindow &window;

		PlayerInput input;
		PlayerPhysics physics;
		PlayerGraphics graphics;
	public:
		Character(sf::Vector2f position, const std::string & assetName, AssetManager & assets, sf::RenderWindow &window);
		void update(sf::RenderWindow & window, World & world);
		void attack();
		void draw();

};

#endif //__CHARACTER_HPP