#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"
#include "World.hpp"
#include "Game.hpp"
#include "Editor.hpp"
#include "Character.hpp"
#include "Interface.hpp"


int main(){

	sf::RenderWindow window{ sf::VideoMode{ 1000, 580 }, "The Warden"};

	sf::Event event;
	AssetManager assets;
	Game game(window, assets);
	Interface interface(game, assets, window);

	sf::Clock clock;
	uint_fast8_t msPerUpdate = 16.67;
	double previous, lag, current, elapsed;


	while (window.isOpen()){	
		current = (clock.getElapsedTime().asMilliseconds());
		elapsed = current - previous;
		previous = current;
		lag += elapsed;

		game.handleInput(event);
		interface.handleInput(event);

		while (lag >= msPerUpdate){
			game.handleInput(event);
			interface.handleInput(event);
			lag -= msPerUpdate;
		}

		while(window.pollEvent(event)){
			if( event.type == sf::Event::Closed ){
				window.close();
			}
			game.handleInput(event);
			interface.handleInput(event);
		}

		window.clear();
		game.display();
		interface.display();
		window.display();

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			return 0;
		}

	}

	return 0;
}

//(1920,1080) (5,3) (1,1) (1,0) | (0,0) (1,2) | idle | waterBubble