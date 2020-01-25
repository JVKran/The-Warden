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

using namespace std;
using namespace cv;

class PlayerInput : public InputComponent {
	public:
		PlayerInput(World & world, std::vector<Character> & characters):
			InputComponent(world, characters)
		{}
		virtual void processInput(const sf::Vector2f & position, sf::Vector2f & direction, std::vector<KeyBinding> & keys) override;
		virtual void addTile(const sf::Event & event, World & world, sf::RenderWindow & window, sf::View & view) override;
		virtual void deleteTile(const sf::Event & event, World & world, sf::RenderWindow & window, sf::View & view) override;
		virtual void processItemUsage(std::vector<std::shared_ptr<Item>> & items, Character * ownCharacter) override;
		virtual void handleEvent(const sf::Event & event, int_fast16_t & selectedItem) override;
		void handleInteraction(World & world);

		PlayerInput & operator=(PlayerInput lhs){
			world = lhs.world;
			characters = lhs.characters;
			return *this;
		}
};

class InteractiveInput : public PlayerInput {
	private:
	    bool isCreated = false;
	    static void detectPosition( sf::Vector2f & direction );
	public:
		InteractiveInput(World & world, std::vector<Character> & characters):
			PlayerInput(world, characters)
		{}

		virtual void processInput(const sf::Vector2f & position, sf::Vector2f & direction, std::vector<KeyBinding> & keys){
			if(!isCreated){
				thread inputThread(detectPosition, std::ref(direction));
				inputThread.detach();
				isCreated = true;
				std::cout << "Detached" << std::endl;
			}
		}
};

class PlayerGraphics : public GraphicsComponent {
	public:
		PlayerGraphics(const std::string & assetName, AssetManager & assets);

		virtual void processGraphics(sf::RenderWindow & window, const sf::Vector2f & position, sf::View & view) override;

		PlayerGraphics & operator=(PlayerGraphics lhs){
			sprite = lhs.sprite;
			return *this;
		}
};

class AnimatedPlayerGraphics : public AnimatedGraphicsComponent {
	public:
		AnimatedPlayerGraphics(const std::string & assetName, AssetManager & assets, SpriteCharacter & characterData);

		virtual void processViewChanges(sf::View & view, const sf::Vector2f & position) override;
};

#endif //__PLAYER_HPP