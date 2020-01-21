#ifndef __ENEMY_HPP
#define __ENEMY_HPP

#include <SFML/Graphics.hpp>
#include "World.hpp"
#include "AssetManager.hpp"
#include "Character.hpp"
#include "SpriteAnimation.hpp"

// class EnemyPhysics : public PhsysicsComponent {
// 	private:
		
// };

class EnemyInput : public InputComponent {
	public:
		virtual void processInput(const sf::Vector2f & velocity, const sf::Vector2f & position, sf::Vector2f & direction, const std::vector<Character> & characters) override;
};

class EnemyGraphics : public GraphicsComponent{
	public:
		EnemyGraphics(const std::string & assetName, AssetManager & assets);

		virtual void processGraphics(sf::RenderWindow & window, const sf::Vector2f & position, sf::View & view) override;
};


#endif //__ENEMY_HPP