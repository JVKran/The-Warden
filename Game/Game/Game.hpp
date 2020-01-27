/// @file

#ifndef __GAME_HPP
#define __GAME_HPP

#include <string>
#include "Editor.hpp"
#include "World.hpp"
#include <SFML/Graphics.hpp>
#include "FactoryFunction.hpp"
#include "Character.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "LootDrop.hpp"
#include "keybinding.hpp"
#include <memory>
#include <array>
#include "Audio.hpp"

/// \brief
/// Game
/// \details
/// This class is the entire Game. It contains everything that's needed to run the game. 
/// It features two functions that should be called from the Game Loop (that's located in the main())
/// that, based on the state, call several other functions to handle input, process physics and manage graphics.
class Game {
	private:
		AssetManager assets;					//!< The AssetManager to retrieve Textures from.
		World world;							//!< The World to use while playing (in state PLAYING).

		sf::Font font;
		sf::Text text;

		sf::Font experienceFont;
		sf::Text experienceText;

		sf::Clock clock;
		double lastTime;
		int_fast16_t remainingGameTime = 600;
		
		std::vector<Character> characters;		//!< All Characters currently active in the Game.

		sf::RenderWindow & window;
		std::vector<KeyBinding> & bindings;

		void loadCharacters();
	public:
		Game(sf::RenderWindow & window, AssetManager & assets, std::vector<KeyBinding> & bindings);
		~Game(){
			window.close();
		}
		void startWorld(const std::string & worldName);

		void restartClocks();
		void handleInput(sf::View & view,  const sf::Event & event);
		void handleEvent(const sf::Event & event, sf::View & view);
		void display(sf::View & view);
};


#endif //__GAME_HPP