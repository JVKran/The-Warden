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
		virtual void processInput(const sf::Vector2f & position, sf::Vector2f & direction) override;
		virtual void processItemUsage(std::vector<std::shared_ptr<Item>> & items, Character * ownCharacter){
			items[0]->use(ownCharacter, characters);
		}
};

class EnemyGraphics : public GraphicsComponent {
	public:
		EnemyGraphics(const std::string & assetName, AssetManager & assets);

		virtual void processGraphics(sf::RenderWindow & window, const sf::Vector2f & position, sf::View & view) override;
};


#endif //__ENEMY_HPP