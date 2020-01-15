#ifndef __CHARACTER_HPP
#define __CHARACTER_HPP

#include <SFML/Graphics.hpp>
#include "World.hpp"
#include "Attack.hpp"
#include "Weapon.hpp"

class PhysicsComponent {
	public:
		virtual void processPhysics(World & world, sf::Vector2f & position) = 0;
};

class InputComponent {
	public:
		virtual void processInput(sf::Vector2f & velocity) = 0;
};

class PlayerPhysics : public PhysicsComponent {
	private:
		enum class states { JUMPING, STANDING, CROUCHING, FALLING};
		states state = states::STANDING;
	public:
		virtual void processPhysics(World & world, sf::Vector2f & position);
};

class PlayerInput : public InputComponent {
	public:
		virtual void processInput(sf::Vector2f & velocity);
};

class Character {
	private:
		sf::Vector2f position;
		sf::Vector2f velocity;

		sf::Sprite sprite;

		PlayerInput input;
		PlayerPhysics physics;

		Attack & attack;
		float health;
	public:
		void update(sf::RenderWindow & window, World & world);
		void attack();
		void draw();

};

#endif //__CHARACTER_HPP