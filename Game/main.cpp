#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"
#include "World.hpp"
#include "Editor.hpp"
#include "Character.hpp"

int main(){
	#define playmode
	AssetManager assets;
	assets.loadObjects("objects.txt");

	sf::View view(sf::FloatRect(0.f, 0.f, 1000.f, 580.f));

	#ifdef playmode
	World world(assets, "world.txt", view);		//Create world with world.txt as config
	#else
	Editor editor( assets, "world.txt", view );	//Edit world world.txt
	#endif
	sf::RenderWindow window{ sf::VideoMode{ 1000, 580 }, "The Warden" };

	sf::Clock clock;
	uint_fast8_t msPerUpdate = 16;
	double previous, lag, current, elapsed;
	Character speler(sf::Vector2f(500,100),"crate",assets,window);
	window.setVerticalSyncEnabled(1);

	while (window.isOpen()){
		current = (clock.getElapsedTime().asMilliseconds());
		elapsed = current - previous;
		previous = current;
		lag += elapsed;

		// processInput();

		//editor.handleInput(window);

		while (lag >= msPerUpdate){
			//editor.handleInput(window);
			lag -= msPerUpdate;
		}
		#ifdef playmode

		
		window.clear();
		world.draw(window);
		speler.update(window, world);
		window.setView(view);
		window.display();
		
		#else
		window.clear();
		editor.draw( window );
		window.setView(view);
		window.display();

		#endif

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
				window.close();
		}

		sf::Event event;		
	    while( window.pollEvent(event) ){
			if( event.type == sf::Event::Closed ){
				window.close();
			}
		}

	}
	#ifndef playmode
	editor.editingDone();
	#endif
	return 0;
}