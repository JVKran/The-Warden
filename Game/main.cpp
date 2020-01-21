#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"
#include "World.hpp"
#include "Game.hpp"
#include "Editor.hpp"
#include "Character.hpp"
#include "Interface.hpp"
#include "StateMachine.hpp"


int main(){

	sf::RenderWindow window{ sf::VideoMode{ 1000, 580 }, "The Warden"};
	sf::View view = sf::View(sf::FloatRect(0.f, 0.f, 1000.f, 580.f));

	sf::Event event;
	AssetManager assets;

	Game game(window, assets);
	Editor editor(window, assets);
	Interface interface(game, editor, assets, window);
	StateMachine machine(game, interface, editor);

	sf::Clock clock;
	//uint_fast8_t msPerUpdate = 16.67;
	double previous, lag, current, elapsed;


	while (window.isOpen()){	
		current = (clock.getElapsedTime().asMilliseconds());
		elapsed = current - previous;
		previous = current;
		lag += elapsed;

		machine.handleInput(event, view);

		// while (lag >= msPerUpdate){
		// 	machine.handleEvent(event, view);
		// 	lag -= msPerUpdate;
		// }

		window.clear();
		window.setView(view);
		machine.display(event, view);
		window.display();

		while(window.pollEvent(event)){
			if( event.type == sf::Event::Closed ){
				window.close();
			}
			machine.handleEvent(event, view);
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			return 0;
		}

	}

	return 0;
}

//(1920,1080) (5,3) (1,1) (1,0) | (0,0) (1,2) | idle | waterBubble