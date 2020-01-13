#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"

int main(){
	sf::RenderWindow window{ sf::VideoMode{ 1000, 580 }, "The Warden" };

	AssetManager assets;
	assets.loadObjects("objects.txt");

	sf::Sprite sprite;
	sprite.setTexture(assets.getTexture("bush"));
	window.draw(sprite);

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
		window.draw(sprite);
		window.display();
		sf::sleep( sf::milliseconds( 10 ));

		sf::Event event;		
	    while( window.pollEvent(event) ){
			if( event.type == sf::Event::Closed ){
				window.close();
			}
		}
		// render();

	}
	return 0;
}