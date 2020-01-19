#ifndef __CHARACTER_HPP
#define __CHARACTER_HPP

#include <SFML/Graphics.hpp>
#include "World.hpp"
#include "SpriteAnimation.hpp"
#include <memory>

struct spriteCharacter {
	std::vector<sf::Vector2i> spriteCharacterData;
	std::vector<sf::Vector2i> spriteCharacterAction;
	std::vector<std::string> spriteCharacterNames;

	spriteCharacter(std::vector<sf::Vector2i> spriteCharacterData, std::vector<sf::Vector2i> spriteCharacterAction, std::vector<std::string> spriteCharacterNames):
		spriteCharacterData(spriteCharacterData),
		spriteCharacterAction(spriteCharacterAction),
		spriteCharacterNames(spriteCharacterNames)
	{}
};

class PhysicsComponent {
	public:
		virtual void processPhysics(World & world, sf::Vector2f & position, sf::Vector2f &velocity, const sf::Vector2f & dimensions) = 0;
};

class InputComponent {
	public:
		virtual void processInput(sf::Vector2f & velocity) = 0;
};

class GraphicsComponent {
	protected:
		sf::Sprite sprite;
		spriteCharacter characterData;

		sf::Clock clock;
		sf::Time previousTime;

		sf::Vector2f previousPosition;

		enum class states {IDLE, WALK, JUMP};
		states state = states::JUMP;
		bool isIdle = true;
		bool isWalkingLeft = false;
	public:
		GraphicsComponent(const std::string & assetName, AssetManager & assets, spriteCharacter & characterData);

		virtual void processGraphics(sf::RenderWindow & window, const sf::Vector2f & position, sf::View & view) = 0;
		virtual sf::Vector2f getDimensions() = 0;
};

class Character {
	private:
		sf::Vector2f position;
		sf::Vector2f velocity;

		std::shared_ptr<InputComponent> input;
		std::shared_ptr<PhysicsComponent> physics;
		std::shared_ptr<GraphicsComponent> graphics;
	public:
		Character(sf::Vector2f position,
						std::shared_ptr<InputComponent> input, std::shared_ptr<PhysicsComponent> physics, std::shared_ptr<GraphicsComponent> graphics);

		void update(sf::RenderWindow & window, World & world);
		void attack();
		void draw(sf::RenderWindow & window, sf::View & view);

};

#endif //__CHARACTER_HPP