/// @file

#ifndef __PLAYER_HPP
#define __PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "World.hpp"
#include "AssetManager.hpp"
#include "Character.hpp"
#include "SpriteAnimation.hpp"

class PlayerInput : public InputComponent {
	public:
		PlayerInput(World & world, std::vector<Character> & characters):
			InputComponent(world, characters)
		{}
		virtual void processInput(const sf::Vector2f & position, sf::Vector2f & direction, std::array< KeyBinding, 3 > & keys) override;
		virtual void addTile(const sf::Event & event, World & world, sf::RenderWindow & window, sf::View & view) override;
		virtual void deleteTile(const sf::Event & event, World & world, sf::RenderWindow & window, sf::View & view) override;
		virtual void processItemUsage(std::vector<std::shared_ptr<Item>> & items, Character * ownCharacter);

		PlayerInput & operator=(PlayerInput lhs){
			world = lhs.world;
			characters = lhs.characters;
			return *this;
		}
};

class PlayerGraphics : public GraphicsComponent {
	public:
		PlayerGraphics(const std::string & assetName, AssetManager & assets);

		virtual void processGraphics(sf::RenderWindow & window, const sf::Vector2f & position, sf::View & view) override;
		virtual sf::Vector2f getDimensions() override;

		PlayerGraphics & operator=(PlayerGraphics lhs){
			sprite = lhs.sprite;
			return *this;
		}
};

#endif //__PLAYER_HPP