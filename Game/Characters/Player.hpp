/// @file

#ifndef __PLAYER_HPP
#define __PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "World.hpp"
#include "AssetManager.hpp"
#include "Character.hpp"
#include "SpriteAnimation.hpp"
#include <iostream>
#include <exception>
#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <thread> 

/// \brief
/// PlayerInput.
/// \details
/// This class implements the input for players. This consists of reading basic assignable input, item selection and item usage.
class PlayerInput : public InputComponent {
	public:
		PlayerInput(World & world, std::vector<Character> & characters):
			InputComponent(world, characters)
		{}
		
		virtual void processInput(const sf::Vector2f & position, sf::Vector2f & direction, std::vector<KeyBinding> & keys) override;
		virtual void addTile(const sf::Event & event, World & world, sf::RenderWindow & window, sf::View & view) override;
		virtual void addTile(Tile & tile);
		virtual void deleteTile(const sf::Event & event, World & world, sf::RenderWindow & window, sf::View & view) override;
		virtual void processItemUsage(const sf::Event & event, std::vector<std::shared_ptr<Item>> & items, Character * ownCharacter) override;

		PlayerInput & operator=(PlayerInput lhs){
			world = lhs.world;
			characters = lhs.characters;
			return *this;
		}
};

/// \brief
/// Interactive PlayerInput.
/// \details
/// This class implements the interactive input for players. This consists of reading basic left, right and jump input based on visual input
/// retrieved from a detached thread.
class InteractiveInput : public PlayerInput {
	private:
	    bool isCreated = false;										//!< Whether the vision is enabled.
	    static void detectPosition( sf::Vector2f & direction );
	public:
		InteractiveInput(World & world, std::vector<Character> & characters):
			PlayerInput(world, characters)
		{}

		virtual void processInput(const sf::Vector2f & position, sf::Vector2f & direction, std::vector<KeyBinding> & keys);
};

/// \brief
/// PlayerGraphics.
/// \details
/// This class implements the graphics for players. Not very different; just changes the view according to the position.
class PlayerGraphics : public GraphicsComponent {
	public:
		PlayerGraphics(const std::string & assetName, AssetManager & assets);

		virtual void processGraphics(sf::RenderWindow & window, const sf::Vector2f & position, sf::View & view) override;

		PlayerGraphics & operator=(PlayerGraphics lhs){
			sprite = lhs.sprite;
			return *this;
		}
};

/// \brief
/// PlayerGraphics.
/// \details
/// This class implements the graphics for players. Not very different; just changes the view according to the position.
class AnimatedPlayerGraphics : public AnimatedGraphicsComponent {
	public:
		AnimatedPlayerGraphics(const std::string & assetName, AssetManager & assets, SpriteCharacter & characterData);

		virtual void processViewChanges(sf::View & view, const sf::Vector2f & position) override;
};

#endif //__PLAYER_HPP