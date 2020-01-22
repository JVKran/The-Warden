/// @file

#ifndef __CHARACTER_HPP
#define __CHARACTER_HPP

#include <SFML/Graphics.hpp>
#include "World.hpp"
#include "SpriteAnimation.hpp"
#include <memory>

/// \brief
/// Data needed for SpriteAnimation.
/// \details
/// This class contains all data needed for a functioning SpriteAnimation. This just enables the developers
/// to pass all these vectors in one object instead of all vectors single.
struct SpriteCharacter {
	std::vector<sf::Vector2i> spriteCharacterData;
	std::vector<sf::Vector2i> spriteCharacterAction;
	std::vector<std::string> spriteCharacterNames;


	SpriteCharacter(std::vector<sf::Vector2i> spriteCharacterData, std::vector<sf::Vector2i> spriteCharacterAction, std::vector<std::string> spriteCharacterNames);
};

/// \brief
/// Physicscomponent for Characters.
/// \details
/// This class is responsible for updating and managing physics for a Character.
class PhysicsComponent {
	public:
		virtual void processPhysics(World & world, sf::Vector2f & position, sf::Vector2f & velocity, sf::Vector2f & direction, const sf::Vector2f & dimensions) = 0;
};

/// \brief
/// Inputcomponent for Characters.
/// \details
/// This class is responsible for managing input for a Character.
class InputComponent {
	public:
		virtual void processInput(sf::Vector2f & direction) = 0;
};

/// \brief
/// Graphicscomponent for Characters.
/// \details
/// This class is responsible for managing all graphics related actions.
class GraphicsComponent {
	protected:
		sf::Sprite sprite;
		sf::Sprite spritei;
		SpriteCharacter characterData;

		sf::Clock clock;
		sf::Time previousTime;

		sf::Vector2f previousPosition;

		enum class states {IDLE, WALK, JUMP};
		states state = states::JUMP;
		bool isIdle = true;
		bool isWalkingLeft = false;
	public:
		GraphicsComponent(const std::string & assetName, AssetManager & assets, SpriteCharacter & characterData);

		virtual void processGraphics(sf::RenderWindow & window, const sf::Vector2f & position, sf::View & view) = 0;
		virtual sf::Vector2f getDimensions() = 0;
};

/// \brief
/// Character
/// \details
/// This class features a Character. Every character is the same, except for the (possibly) different components.
/// The functioning of a Character is defined completely in its components; The component pattern has been used here.
class Character {
	private:
		sf::Vector2f position;
		sf::Vector2f velocity;
		sf::Vector2f direction;

		std::shared_ptr<InputComponent> input;			//!< A smart pointer to an on the heap allocated InputComponent.
		std::shared_ptr<PhysicsComponent> physics;		//!< A smart pointer to an on the heap allocated PhysicsComponent.
		std::shared_ptr<GraphicsComponent> graphics;	//!< A smart pointer to an on the heap allocated GraphicsComponent.
	public:
		Character(sf::Vector2f position, std::shared_ptr<InputComponent> input, std::shared_ptr<PhysicsComponent> physics, std::shared_ptr<GraphicsComponent> graphics);

		void update(sf::RenderWindow & window, World & world);
		void attack();
		void draw(sf::RenderWindow & window, sf::View & view);

};

#endif //__CHARACTER_HPP