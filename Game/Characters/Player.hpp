/// @file

#ifndef __PLAYER_HPP
#define __PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "World.hpp"
#include "AssetManager.hpp"
#include "Character.hpp"
#include "SpriteAnimation.hpp"
#include "bindings.hpp"

class PlayerInput : public InputComponent {
	public:
		PlayerInput(World & world, std::vector<Character> & characters):
			InputComponent(world, characters)
		{}
		virtual void processInput(const sf::Vector2f & position, sf::Vector2f & direction) override;
};

class PlayerGraphics : public GraphicsComponent {
	public:
		PlayerGraphics(const std::string & assetName, AssetManager & assets);

		virtual void processGraphics(sf::RenderWindow & window, const sf::Vector2f & position, sf::View & view) override;
		virtual sf::Vector2f getDimensions() override;
};

#endif //__PLAYER_HPP