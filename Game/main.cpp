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
	assets.loadObjects("Assets/objects.txt");

	sf::View view(sf::FloatRect(0.f, 0.f, 1000.f, 580.f));

	#ifdef playmode
	World world(assets, "World/world.txt", view);		//Create world with world.txt as config
	#else
	Editor editor( assets, "World/world.txt", view );	//Edit world world.txt
	#endif
	sf::RenderWindow window{ sf::VideoMode{ 1000, 580 }, "The Warden", sf::Style::Resize};

	sf::Clock clock;
	uint_fast8_t msPerUpdate = 16.67;
	double previous, lag, current, elapsed;
	Character speler(sf::Vector2f(500,100),"crate",assets,window);
	window.setVerticalSyncEnabled(1);
	window.setFramerateLimit(60);
	lag=0;
	elapsed=0;


	while (window.isOpen()){
		current = (clock.getElapsedTime().asMilliseconds());
		//elapsed = current - previous;

		//lag += elapsed;

		// processInput();

				window.clear();
		world.draw(window);
		speler.update(window, world);		
		window.setView(view);

		while (current-previous<msPerUpdate){
		#ifdef playmode

		

		window.display();
		
		#else
		window.clear();
		editor.draw( window );
		window.setView(view);
		window.display();
				previous= current;
		#endif
			//lag -= msPerUpdate;
		current = (clock.getElapsedTime().asMilliseconds());
		}
		previous=current;

		#ifndef playmode
		editor.handleInput(window);
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
	current = (clock.getElapsedTime().asMilliseconds());
	//previous = current;
	}

	#ifndef playmode
	editor.editingDone();
	#endif
	return 0;
}