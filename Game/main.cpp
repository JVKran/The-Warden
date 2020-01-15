#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"
#include "World.hpp"
#include "Editor.hpp"

int main(){
	AssetManager assets;
	assets.loadObjects("objects.txt");

	World world(assets, "world.txt");		//Create world with world.txt as config

	Editor editor( assets,"world.txt" );	//Edit world world.txt

	sf::RenderWindow window{ sf::VideoMode{ 1000, 580 }, "The Warden" };

	sf::Clock clock;
	uint_fast8_t msPerUpdate = 16;
	double previous, lag, current, elapsed;

	while (window.isOpen()){
		current = (clock.getElapsedTime().asMilliseconds());
		elapsed = current - previous;
		previous = current;
		lag += elapsed;

		// processInput();

		while (lag >= msPerUpdate){
			lag -= msPerUpdate;
		}

		window.clear();
		editor.handleInput(window);
		editor.draw( window );
		// world.draw(0, 1000, window);
		window.display();

		sf::Event event;		
	    while( window.pollEvent(event) ){
			if( event.type == sf::Event::Closed ){
				window.close();
			}
		}

	}
	editor.editingDone();
	return 0;
}