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
#include <memory>

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
		Editor editor;							//!< The Editor to edit World 's with.'
		
		std::vector<Character> characters;		//!< All Characters currently active in the Game.

		sf::Event event;						//!< The Event that's used to handle more complex input.
		sf::RenderWindow window{ sf::VideoMode{ 1920, 1080 }, "The Warden", sf::Style::Resize};
		sf::View view = sf::View(sf::FloatRect(0.f, 0.f, 1920.f, 1080.f));

		enum class states {PLAYING, EDITING, PAUSED};
		states state = states::PLAYING;

		void loadCharacters();
	public:
		Game(const std::string & objectConfigurationFile);
		~Game(){
			window.close();
		}

		void startWorld(const std::string & worldName);
		void editWorld(const std::string & worldName);

		void handleInput();
		void display();
};


#endif //__GAME_HPP