#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"
#include "World.hpp"

int main(){
	AssetManager assets;
	assets.loadObjects("objects.txt");

	World world(assets);
	world.loadWorld("world.txt");
	world.setBackground("background");

	sf::RenderWindow window{ sf::VideoMode{ 1000, 580 }, "The Warden" };

	sf::Clock clock;
	uint_fast8_t msPerUpdate = 16;
	double previous, lag, current, elapsed;
	sf::View view(sf::FloatRect(0.f, 0.f, 1000.f, 580.f));
	window.setView(view);
	while (window.isOpen()){
		current = (clock.getElapsedTime().asMilliseconds());
		elapsed = current - previous;
		previous = current;
		lag += elapsed;

		// processInput();

		while (lag >= msPerUpdate){
			lag -= msPerUpdate;
		}



		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
{
    		view.move(-1.f, 0.f);
					window.setView(view);
}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
{
    		view.move(1.f, 0.f);
					window.setView(view);
}






		window.clear();
		//world.setBackground("background");
		world.draw(window);
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