#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>

int main(){
	sf::Clock clock;
	uint_fast8_t msPerUpdate = 16;

	double previous, lag, current, elapsed;

	while (true){
		current = (clock.getElapsedTime().asMilliseconds());
		elapsed = current - previous;
		previous = current;
		lag += elapsed;

		// processInput();

		while (lag >= msPerUpdate){
			lag -= msPerUpdate;
		}

		// render();

	}
	return 0;
}