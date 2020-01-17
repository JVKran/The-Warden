#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"
#include "World.hpp"
#include "Game.hpp"
#include "Editor.hpp"
#include "Character.hpp"


int main(){
	Game game("Assets/objects.txt");

	bool playMode;
	std::cout << "Play (1) or edit (0)?" << std::endl;
	std::cin >> playMode;

	if(playMode){
		game.startWorld("World/world.txt");
	} else {
		game.editWorld("World/world.txt");
	}

	sf::Clock clock;
	uint_fast8_t msPerUpdate = 16.67;
	double previous, lag, current, elapsed;


	while (true){	
		current = (clock.getElapsedTime().asMilliseconds());
		elapsed = current - previous;
		previous = current;
		lag += elapsed;

		game.handleInput();

		while (lag >= msPerUpdate){
			game.handleInput();
			lag -= msPerUpdate;
		}

		game.display();

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			return 0;
		}

	}

	return 0;
}