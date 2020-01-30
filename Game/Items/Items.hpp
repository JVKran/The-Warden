/// @file

#ifndef __ITEMS_HPP
#define __ITEMS_HPP

#include <vector>
#include <cstdint>
#include "Character.hpp"
#include "World.hpp"
#include <memory>
#include <functional>
#include <cmath> 

class Character; 
class World;

/// \brief
/// Item
/// \details
/// This class is an abstract virtual class for all items.
class Item : public Tile {
	protected:
		const std::string assetName;		//!< The AssetManager to use for gathering the needed textures.
		int_fast8_t experience;				//!< The amount of experience to pick up.
	public:
		Item(const std::string assetName, AssetManager & assets, int_fast8_t experience = 0);
		virtual bool use(Character * character, std::vector<Character> & characters){return false;}

		virtual bool containsExperience();
		virtual int_fast8_t getExperience();

		virtual bool isWeapon();
		virtual int_fast16_t getPeriod();

		std::string getName();

		virtual int_fast8_t getAmount(){ return 0; }
		virtual void drawAmount(sf::RenderWindow & window){}
};

/// \brief
/// Weapon
/// \details
/// This class is responsible for hitting other existing Characters and thus dealing damage.
class Weapon : public Item {
	private:	
		sf::Clock clock;				//!< The sf::Clock to use for determining if it is possible to attack again.
		sf::Time lastAttack;			//!< The time when the last attack was performed.
		const int_fast16_t hitPeriod;	//!< The period in milliseconds that should be between two attacks.

		const int damageFactor;
	public:
		Weapon(const std::string assetName, AssetManager & assets, const int damageFactor, const int_fast16_t hitPeriod);
		virtual bool use(Character * character, std::vector<Character> & characters) override;
		virtual bool isWeapon() override;
		virtual int_fast16_t getPeriod() override;
};

/// \brief
/// Consumable
/// \details
/// This class is responsible for replenishing health after the Character consumes a consumable.
class Consumable : public Item {
	private:
		const int_fast8_t foodValue;			//!< The amount of health the Character gets when eating this Consumable.
	public:
		Consumable(const std::string assetName, AssetManager & assets, const int_fast8_t foodValue);
		virtual bool use(Character * character, std::vector<Character> & characters) override;
};

/// \brief
/// Experience
/// \details
/// This class is responsible for adding the picked up experience to the experience of the player who picked it up.
class Experience : public Item {
	public:
		Experience(const std::string assetName, AssetManager & assets, int_fast8_t experience = 0);
		virtual bool containsExperience() override;
		virtual int_fast8_t getExperience() override;
};

/// \brief
/// Block
/// \details
/// This class is responsible for placing and picking up blocks.
class Block : public Item {
	private:
		int_fast8_t amountOfObjects;		//!< The amount of blocks the player can hold
		AssetManager & assets;
		const sf::Event & event; 			//!< Needs an event for the use function
		World & world;						//!< Needs a world to add the blocks into the world
		sf::RenderWindow & window;			//!< Needs a window for the use function
		sf::View & view;					//!< Needs a view to get the right mouse position in the use function

		sf::Font blockFont;					//!< The sf::Font to use for displaying the amount of blocks.
		sf::Text blockText;					//!< The sf::Text to use for displaying the amount of blocks.

	public:
		Block(const std::string assetName, AssetManager & assets, int_fast8_t amountOfObjects, const sf::Event & event, World & world, sf::RenderWindow & window, sf::View & view);
		virtual bool use(Character * character, std::vector<Character> & characters) override;
		virtual int_fast8_t getAmount(){ return amountOfObjects; }
		virtual void drawAmount(sf::RenderWindow & window);
};

#endif //Items.hpp