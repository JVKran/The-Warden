#ifndef __ENEMY_HPP
#define __ENEMY_HPP

#include <SFML/Graphics.hpp>
#include "World.hpp"
#include "AssetManager.hpp"
#include "Character.hpp"
#include "SpriteAnimation.hpp"

class EnemyPhysics : public PhysicsComponent {
	public:
		virtual void processVelocity(sf::Vector2f & direction, sf::Vector2f & velocity) override;
};

class EnemyInput : public InputComponent {
	public:
		EnemyInput(World & world, std::vector<Character> & characters):
			InputComponent(world, characters)
		{}
		virtual void processInput(const sf::Vector2f & position, sf::Vector2f & direction, std::array< KeyBinding, 3 > & keys) override;
		virtual void addTile(const sf::Event & event, World & world, sf::RenderWindow & window, sf::View & view) {}
		virtual void deleteTile(const sf::Event & event, World & world, sf::RenderWindow & window, sf::View & view) {}
		virtual void processItemUsage(std::vector<std::shared_ptr<Item>> & items, Character * ownCharacter){
			items.at(0)->use(ownCharacter, characters);
		}

		EnemyInput & operator=(EnemyInput lhs){
			world = lhs.world;
			characters = lhs.characters;
			return *this;
		}
};

class EnemyGraphics : public GraphicsComponent {
	public:
		EnemyGraphics(const std::string & assetName, AssetManager & assets);

		virtual void processGraphics(sf::RenderWindow & window, const sf::Vector2f & position, sf::View & view) override;

		EnemyGraphics & operator=(EnemyGraphics lhs){
			sprite = lhs.sprite;
			return *this;
		}
};


#endif //__ENEMY_HPP