#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"
#include "World.hpp"
#include "Editor.hpp"
#include "Character.hpp"

int main(){
	AssetManager assets;
	assets.loadObjects("objects.txt");

	sf::View view(sf::FloatRect(0.f, 0.f, 1000.f, 580.f));
	//World world(assets, "world.txt", view);		//Create world with world.txt as config
	Editor editor( assets, "world.txt", view );	//Edit world world.txt
	sf::RenderWindow window{ sf::VideoMode{ 1000, 580 }, "The Warden" };

	sf::Clock clock;
	uint_fast8_t msPerUpdate = 4;
	double previous, lag, current, elapsed;
	std::vector<sf::Vector2i> spritePlayerData(sf::Vector2i{350,592},sf::Vector2i{7,16}, sf::Vector2i{5,5}, sf::Vector2i{3,0});
	std::vector<sf::Vector2i> spritePlayerAction( sf::Vector2i{0,0}, sf::Vector2i{3,0}, sf::Vector2i{3,3},sf::Vector2i{6,1}, sf::Vector2i{1,1},sf::Vector2i{0,0});
	std::vector<std::string> spritePlayerNames("idle","slide", "walk");
	Character speler(sf::Vector2f(500,100),"player",assets,window, spritePlayerData, spritePlayerAction, spritePlayerNames);

	while (window.isOpen()){
		current = (clock.getElapsedTime().asMilliseconds());
		elapsed = current - previous;
		previous = current;
		lag += elapsed;

		// processInput();

		editor.handleInput(window);
		while (lag >= msPerUpdate){
			editor.handleInput(window);
			lag -= msPerUpdate;
		}

		window.clear();
		editor.draw( window );
		window.setView(view);
		window.display();

		// window.clear();
		// world.draw(window);
		speler.update(window, world);
		// window.setView(view);
		// window.display();

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
	
	editor.editingDone();
	return 0;
}