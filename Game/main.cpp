#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"
#include "World.hpp"
#include "Editor.hpp"
#include "Character.hpp"


int main(){
	bool playMode;
	std::cout << "Play (1) or edit (0)?" << std::endl;
	std::cin >> playMode;

	AssetManager assets;
	assets.loadObjects("Assets/objects.txt");

	sf::View view(sf::FloatRect(0.f, 0.f, 1000.f, 580.f));

	World world(assets, "World/world.txt", view);		//Create world with world.txt as config
	Editor editor( assets, "World/world.txt", view );	//Edit world world.txt
	sf::RenderWindow window{ sf::VideoMode{ 1000, 580 }, "The Warden", sf::Style::Resize};

	sf::Clock clock;
	uint_fast8_t msPerUpdate = 16.67;
	double previous, lag, current, elapsed;
	Character speler(sf::Vector2f(500,100),"crate",assets,window);


	while (window.isOpen()){
		current = (clock.getElapsedTime().asMilliseconds());
		elapsed = current - previous;
		previous = current;
		lag += elapsed;


		if(playMode){

			while (lag >= msPerUpdate){
				lag -= msPerUpdate;
			}
			
			window.clear();
			world.draw(window);
			speler.update(window, world);
			window.setView(view);
			window.display();
		
		} else {

			editor.handleInput(window);

			while (lag >= msPerUpdate){
				editor.handleInput(window);
				lag -= msPerUpdate;
			}

			window.clear();
			editor.draw( window );
			window.setView(view);
			window.display();

		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			window.close();
		}

	}

	return 0;
}