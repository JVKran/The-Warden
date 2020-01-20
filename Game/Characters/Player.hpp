/// @file

#ifndef __PLAYER_HPP
#define __PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "World.hpp"
#include "AssetManager.hpp"
#include "Character.hpp"
#include "SpriteAnimation.hpp"

class PlayerPhysics : public PhysicsComponent {
	private:
	    double previous, jumpTime, current, elapsed, lastup=0;
		sf::Clock clock;
		sf::Clock upc;
		enum class states { JUMPING, STANDING, FALLING, INSIDE};
		states state = states::FALLING;
	public:
		virtual void processPhysics(World & world, sf::Vector2f & position, sf::Vector2f &velocity, const sf::Vector2f & dimensions) override;
};

class PlayerInput : public InputComponent {
	public:
		virtual void processInput(sf::Vector2f & velocity, const sf::Vector2f & position, const std::vector<Character> & characters) override;
};

class PlayerGraphics : public GraphicsComponent {
	private:
		SpriteAnimation Animation;	
		std::map<std::string, std::vector<sf::Vector2i> > animation;
		std::string lastAnimation;
	public:
		PlayerGraphics(const std::string & assetName, AssetManager & assets, SpriteCharacter & characterData);

		virtual void processGraphics(sf::RenderWindow & window, const sf::Vector2f & position, sf::View & view) override;
		virtual sf::Vector2f getDimensions() override;
};

#endif //__PLAYER_HPP