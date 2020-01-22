#include <ctime>
#include <iostream>
#include <array>
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"
#include "World.hpp"
#include "Game.hpp"
#include "Editor.hpp"
#include "Settings.hpp"
#include "Character.hpp"
#include "Interface.hpp"
#include "StateMachine.hpp"
#include "keybinding.hpp"


int main(){

	sf::RenderWindow window{ sf::VideoMode{ 1000, 580 }, "The Warden"};
	sf::View view = sf::View(sf::FloatRect(0.f, 0.f, 1000.f, 580.f));

	std::array< KeyBinding, 3 > bindings { 
		KeyBinding ( "Left", 		sf::Keyboard::Left,  		Text( "Left : Left", 	sf::Vector2f{500.0, 50.0}, 	1.0, sf::Color::Red, 1 )	),
		KeyBinding ( "Right",		sf::Keyboard::Right, 		Text( "Right : Right", 	sf::Vector2f{500.0, 80.0}, 	1.0, sf::Color::Red, 1 )	),
		KeyBinding ( "Jump", 		sf::Keyboard::Space, 		Text( "Jump : Space", 	sf::Vector2f{500.0, 110.0}, 1.0, sf::Color::Red, 1 )	)
	};

	sf::Event event;
	AssetManager assets;

	Game game(window, assets, bindings);
	Editor editor(window, assets);
	Settings settings(window, assets, bindings);
	Interface interface(game, editor, settings, assets, window);
	StateMachine machine(game, interface, editor, settings);

	sf::Clock clock;
	uint_fast8_t msPerUpdate = 16;
	double startTime;


	while (window.isOpen()){	
		startTime = (clock.getElapsedTime().asMilliseconds());


		for(uint_fast8_t i = 0; i < 15; i++){
			machine.handleInput(event, view);
		}

		if(clock.getElapsedTime().asMilliseconds() - startTime < msPerUpdate){
			window.clear();
			window.setView(view);
			machine.display(event, view);
			window.display();
		}

		while(window.pollEvent(event)){
			if( event.type == sf::Event::Closed ){
				window.close();
			}
			machine.handleEvent(event, view);
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			return 0;
		}

		if(clock.getElapsedTime().asMilliseconds() - startTime < msPerUpdate){
			
			sf::sleep(sf::milliseconds(1));
		}

	}

	return 0;
}

//(1920,1080) (5,3) (1,1) (1,0) | (0,0) (1,2) | idle | waterBubble