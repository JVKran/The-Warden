#ifndef __ENEMY_HPP
#define __ENEMY_HPP

#include <SFML/Graphics.hpp>
#include "World.hpp"
#include "AssetManager.hpp"
#include "Character.hpp"
#include "SpriteAnimation.hpp"

/// \brief
/// EnemyPhysics.
/// \details
/// This class implements the physics for enemies. They aren't that different, they just accelerate slower and
/// have a slower top speed.
class EnemyPhysics : public PhysicsComponent {
	public:
		virtual void processVelocity(sf::Vector2f & direction, sf::Vector2f & velocity) override;
};

/// \brief
/// EnemyInput.
/// \details
/// This class implements the input for enemies. This consists of some very basic AI.
class EnemyInput : public InputComponent {
	public:
		EnemyInput(World & world, std::vector<Character> & characters):
			InputComponent(world, characters)
		{}
		virtual void processInput(const sf::Vector2f & position, sf::Vector2f & direction, std::vector<KeyBinding> & keys) override;
		virtual void addTile(const sf::Event & event, World & world, sf::RenderWindow & window, sf::View & view) {}
		virtual void addTile(Tile & tile) {}
		virtual void deleteTile(const sf::Event & event, World & world, sf::RenderWindow & window, sf::View & view) {}
		virtual void processItemUsage(const sf::Event & event, std::vector<std::shared_ptr<Item>> & items, Character * ownCharacter) override;

		EnemyInput & operator=(EnemyInput lhs);
};

/// \brief
/// EnemyGraphics.
/// \details
/// This class implements the graphics for enemies. Not very different, it just doesn't set the view to the position.
class EnemyGraphics : public GraphicsComponent {
	public:
		EnemyGraphics(const std::string & assetName, AssetManager & assets);

		virtual void processGraphics(sf::RenderWindow & window, const sf::Vector2f & position, sf::View & view) override;

		EnemyGraphics & operator=(EnemyGraphics lhs);
};


#endif //__ENEMY_HPP