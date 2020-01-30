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
/// Under game we understand the game itself, neither the editor nor the interface. Just the World, Characters,
/// Sounds and Character based UI elements. 
/// It features two functions that should be called from the Game Loop (that's located in the main())
/// that, based on the state, call several other functions to handle input, process physics and manage graphics.
class Game {
	private:
		AssetManager assets;					//!< The AssetManager to retrieve Textures from.
		World world;							//!< The World to use while playing (in state PLAYING).

		sf::Font font;							//!< The sf::Font to use for all texts.
		sf::Text scoreText;						//!< The sf::Text used to display the score.
		sf::Text experienceText;				//!< The sf::Text used to display the experience.
		sf::Text saveText;						//!< The sf::Text used to display the savepoints.
		sf::Text highScoreText;					//!< The sf::Text used to display the highscore.

		sf::Sprite timeSprite;					//!< The sf::Sprite used to display the time icon.
		sf::Sprite experienceSprite;			//!< The sf::Sprite used to display the experience icon.
		sf::Sprite savePointSprite;				//!< The sf::Sprite used to display the savepoint icon.
		sf::Sprite highScoreSprite;				//!< The sf::Sprite used to display the highscore icon.

		std::vector<int> scores = {0};			//!< The vector in which all set scores are stored.

		std::vector<int> savePoints = {3940, 14000, 19800, 28950, 36450, 51200};	//!< The x-coordinates of the savepoints.
		int currentSavePoint = 0;									//!< The last checked savepoint.
		int endPoint = 5000;										//!< The endpoint after which the game ends.

		sf::Clock clock;											//!< The sf::Clock to use for determining passed time.
		double lastTime;											//!< The last time the clock has been updated.
		int_fast16_t remainingGameTime = 600;						//!< The remaining game time.
		
		std::vector<Character> characters;							//!< All Characters currently active in the Game.

		sf::RenderWindow & window;									//!< The window in which everything is drawn.
		std::vector<KeyBinding> & bindings;							//!< The keybindings to use in-game.

		std::shared_ptr<InteractiveInput> visionInput;				//!< The thread with the face detecting code running.
		std::shared_ptr<PlayerInput> keyInput;						//!< A shared pointer to the InputComponent detecting keypresses.

		const sf::Event & event; 									//!< The event to use for detecting key- and mousereleases.
		sf::View & view;											//!< The view to use for determining the position.

		void loadCharacters();
	public:
		Game(sf::RenderWindow & window, AssetManager & assets, std::vector<KeyBinding> & bindings, const sf::Event & event, sf::View & view);
		~Game();

		void startWorld(const std::string & worldName);
		void restart();

		void restartClocks();
		void handleInput(sf::View & view,  const sf::Event & event);
		void handleEvent(const sf::Event & event, sf::View & view);
		void display(sf::View & view);
};


#endif //__GAME_HPP