	sf::RenderWindow window{ sf::VideoMode{ 1000, 580 }, "The Warden" };


#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"
#include "World.hpp"
#include "Character.hpp"
int main(){
	AssetManager assets;
	assets.loadObjects("objects.txt");
	sf::View view(sf::FloatRect(0.f, 0.f, 1000.f, 580.f));
	World world(assets,view);
	world.loadWorld("world.txt");



	sf::Clock clock;
	uint_fast8_t msPerUpdate = 16;
	double previous, lag, current, elapsed;
	Character speler(sf::Vector2f(500,100),"crate",assets,window);

	while (window.isOpen()){
		current = (clock.getElapsedTime().asMilliseconds());
		elapsed = current - previous;
		previous = current;
		lag += elapsed;

		// processInput();

		while (lag >= msPerUpdate){
			lag -= msPerUpdate;
		}
		//window.setView(view);
		speler.update(window, world);
		window.clear();

		world.draw(window);
		speler.draw();
				window.setView(view);
		window.display();
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
				window.close();
		}
		sf::sleep( sf::milliseconds( 10 ));

		sf::Event event;		
	    while( window.pollEvent(event) ){
			if( event.type == sf::Event::Closed ){
				window.close();
			}
		}

	}
	return 0;
}