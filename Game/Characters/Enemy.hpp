#ifndef __ENEMY_HPP
#define __ENEMY_HPP

#include <SFML/Graphics.hpp>
#include "World.hpp"
#include "AssetManager.hpp"
#include "Character.hpp"
#include "SpriteAnimation.hpp"

// class EnemyPhysics : public PhsysicsComponent {

// };

class EnemyInput : public InputComponent {
	public:
		virtual void processInput(sf::Vector2f & velocity, const sf::Vector2f & position, const std::vector<Character> & characters) override;
};


#endif //__ENEMY_HPP