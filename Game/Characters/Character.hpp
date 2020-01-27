/// @file

#ifndef __CHARACTER_HPP
#define __CHARACTER_HPP

#include <SFML/Graphics.hpp>
#include "World.hpp"
#include "SpriteAnimation.hpp"
#include "Items.hpp"
#include "keybinding.hpp"
#include <memory>
#include <vector>
#include "LootDrop.hpp"

class Character;
class Item;
class LootDrop;

/// \brief
/// Data needed for processing collisions.
/// \details
/// This struct contains the bounds to check for collisions in between.
struct CollisionBounds {
	int leftCollisionBound;
	int rightCollisionBound;
};

/// \brief
/// Data needed for SpriteAnimation.
/// \details
/// This class contains all data needed for a functioning SpriteAnimation. This just enables the developers
/// to pass all these strings in one object instead of all strings one by one.
struct SpriteCharacter {
	std::string idleName;
	std::string idleFile;
	std::string jumpName;
	std::string jumpFile;
	std::string walkName;
	std::string walkFile;
	std::string attackName;
	std::string attackFile;
	std::string dieName;
	std::string dieFile;


	SpriteCharacter(std::string idleName, std::string idleFile, std::string jumpName, 
					std::string jumpFile, std::string walkName, std::string walkFile, 
					std::string attackName, std::string attackFile, std::string dieName, 
					std::string dieFile);
};

/// \brief
/// Physicscomponent for Characters.
/// \details
/// This class is responsible for updating and managing physics for a Character.
class PhysicsComponent {
	protected:
		enum class states {JUMPING, STANDING, FALLING, INSIDE};					//!< The states the character can be in.
		states state = states::FALLING;											//!< The state the character currently is in.
		
		bool bottomCollision, topCollision, leftCollision, rightCollision;		//!< Booleans for determining wether or not collisions are taking place.
		bool characterCollision;												//!< Wether or not there's a collision between another character.
		bool hasResistance = false;												//!< Wether or not the character has resistance. i.e. is in water.
	public:
		virtual void processPhysics(sf::Vector2f & velocity);
		virtual void processCollisions(std::vector<std::shared_ptr<Item>> & characterItems, World & world, sf::Vector2f & position, const sf::Vector2f & dimensions, CollisionBounds & collisionBounds, std::vector<Character> & characters, Character * ownCharacter);
		virtual void processVelocity(sf::Vector2f & direction, sf::Vector2f & velocity);

		PhysicsComponent & operator=(PhysicsComponent lhs);
};

/// \brief
/// Inputcomponent for Characters.
/// \details
/// This class is responsible for managing input for a Character.
class InputComponent {
	protected:
		World & world;															//!< The world to use for determining AI paths.
		std::vector<Character> & characters;									//!< The characters that could be followed.
	public:
		InputComponent(World & world, std::vector<Character> & characters):
			world(world),
			characters(characters)
		{}
		virtual void processInput(const sf::Vector2f & position, sf::Vector2f & direction, std::vector< KeyBinding> & keys) = 0;
		virtual void addTile(const sf::Event & event, World & world, sf::RenderWindow & window, sf::View & view) = 0;
		virtual void deleteTile(const sf::Event & event, World & world, sf::RenderWindow & window, sf::View & view) = 0;
		virtual void processItemUsage(const sf::Event & event, std::vector<std::shared_ptr<Item>> & items, Character * ownCharacter) {}
		virtual void handleEvent(const sf::Event & event, int_fast16_t & selectedItem) {}
};

/// \brief
/// Graphicscomponent for Characters.
/// \details
/// This class is responsible for managing all graphics related actions for a single sprite.
class GraphicsComponent {
	protected:
		sf::Sprite sprite;														//!< The sprite to draw on the screen.
	public:
		GraphicsComponent(const std::string & assetName, AssetManager & assets);

		virtual void processGraphics(sf::RenderWindow & window, const sf::Vector2f & position, sf::View & view) = 0;
		virtual sf::Vector2f getDimensions();
};

/// \brief
/// Graphicscomponent for Characters.
/// \details
/// This class is responsible for managing all graphics related actions for a given sprite sheet.
class AnimatedGraphicsComponent {
	protected:
		sf::Sprite spriteIdle;
		sf::Sprite spriteJump;
		sf::Sprite spriteWalk;
		sf::Sprite spriteAttack;
		//SpriteCharacter characterData;

		SpriteAnimation idleAnimation;
		SpriteAnimation jumpAnimation;
		SpriteAnimation walkAnimation;
		SpriteAnimation attackAnimation;
		SpriteAnimation *currentAnimation;	
		std::map<std::string, std::vector<sf::Vector2i> > animation;
		std::string lastAnimation;

		sf::Clock clock;							//!< The clock used to determine when to change to the next sprite in the spritesheet.
		sf::Time previousTime;						//!< The last time the sprite changed.
		sf::Time attackTime;						//!< The time an attack should take.
		sf::Vector2f previousPosition;				//!< The previous position of the sprite.

		enum class states {IDLE, JUMP, WALK};		//!< The states the sprite can be in.
		states state = states::IDLE;				//!< The initial state.
		bool isIdle = true;							//!< Wether or not the character is standing still.
		bool isWalkingLeft = false;					//!< Wether or not the character is walking left.
		bool isAttacking;							//!< Wether or not the character is attacking.
	public:
		AnimatedGraphicsComponent(const std::string & assetName, AssetManager & assets, SpriteCharacter & characterData):
			idleAnimation(assets,spriteIdle,characterData.idleName,characterData.idleFile),
			jumpAnimation(assets,spriteJump,characterData.jumpName,characterData.jumpFile),
			walkAnimation(assets,spriteWalk,characterData.walkName,characterData.walkFile),
			attackAnimation(assets,spriteAttack,characterData.attackName,characterData.attackFile),
			currentAnimation(&idleAnimation)
		{}
		virtual void setFightAnimation(int_fast16_t hitTime=500);
		virtual void processViewChanges(sf::View & view, const sf::Vector2f & position) {}
		virtual void processGraphics(sf::RenderWindow & window, const sf::Vector2f & position, sf::View & view);
		virtual sf::Vector2f getDimensions();
};

/// \brief
/// Character
/// \details
/// This class features a Character. Every character is the same, except for the (possibly) different components.
/// The functioning of a Character is defined completely in its components; The component pattern has been used here.
class Character {
	private:
		sf::Vector2f spawnPosition;								//!< The position the character should go to after death.
		sf::Vector2f position;									//!< The current position of the character.
		sf::Vector2f velocity;									//!< The current velocity of the character.
		sf::Vector2f direction;									//!< The current direction of the character.

		sf::Clock clock;										//!< The clock used for the variable / fluid time step.
		double lastUpdate = 0.0;								//!< The last time the character has been updated.
		double timeDifference = 0.0;							//!< The deltatime between now and the previous update.

		std::shared_ptr<LootDrop> lootDrop;						//!< A smart pointer to an on the heap allocated LootDrop (Hot-Cold splitting).
		std::vector<std::shared_ptr<Item>> items;				//!< A vector of smart pointers to on the heap allocated items.
		int_fast16_t selectedItem = 0;							//!< The number of the currently selected item.
		sf::RectangleShape itemSelector;						//!< The square that's drawn over the selected item.

		bool isPlayerType;										//!< Wheter or not this character is a player.

		int_fast16_t experiencePoints = 0;						//!< The current amount of experience points.
		int_fast8_t health = 100;								//!< The current amount of health.
		sf::RectangleShape healthBar;							//!< The health bar that has to be drawn.

		std::shared_ptr<InputComponent> input;					//!< A smart pointer to an on the heap allocated InputComponent.
		std::shared_ptr<PhysicsComponent> physics;				//!< A smart pointer to an on the heap allocated PhysicsComponent.
		std::shared_ptr<AnimatedGraphicsComponent> graphics;	//!< A smart pointer to an on the heap allocated AnimatedPlayerGraphics.

		CollisionBounds collisionBounds;						//!< The bounds that have to be checked for collisions.
	public:
		Character(sf::Vector2f position, std::shared_ptr<InputComponent> input, std::shared_ptr<PhysicsComponent> physics, std::shared_ptr<AnimatedGraphicsComponent> graphics, std::vector<std::shared_ptr<Item>> startItems, World & world, const bool isPlayerType = false);
		~Character();

		void update(sf::RenderWindow & window, World & world, std::vector<Character> & characters, std::vector<KeyBinding> & keys);
		void addTile(const sf::Event & event, World & world, sf::RenderWindow & window, sf::View & view);
		void deleteTile(const sf::Event & event, World & world, sf::RenderWindow & window, sf::View & view);
		void handleEvent(const sf::Event & event);
		bool isAlive();

		int_fast16_t & getSelectedItemNumber();

		std::shared_ptr<Item> getSelectedItem(){
			return items[selectedItem];
		}
		std::shared_ptr<AnimatedGraphicsComponent> getGraphics(){
			return graphics;
		}
		void setSelectedItemNumber(int_fast16_t number){
				selectedItem = number;
		}
		std::vector<std::shared_ptr<Item>> & getItems();
		bool isPlayer() const;

		sf::Vector2f getPosition() const;
		sf::FloatRect getBounds() const;

		void attack();
		void draw(sf::RenderWindow & window, sf::View & view);

		bool operator!=(const Character & lhs);
		bool operator==(const Character & lhs);
		Character & operator=(Character lhs);

		int_fast16_t getExperience() const;
		void addExperience(const int_fast16_t & experiencePointsToAdd);

		int_fast8_t getHealth() const;
		void setHealth(const int_fast8_t newHealth);

		void setPosition(const sf::Vector2f & newPosition);
		void respawn(){
			position = spawnPosition;
		}
};

#endif //__CHARACTER_HPP