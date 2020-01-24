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

	sf::RenderWindow window{ sf::VideoMode{ 1920, 1080 }, "The Warden", sf::Style::Fullscreen};
	sf::View view = sf::View(sf::FloatRect(0.f, 0.f, 1920.f, 1080.f));

	std::vector<KeyBinding> bindings { 
		KeyBinding ( "Left", 		sf::Keyboard::A,  		Text( "Left : A", 	sf::Vector2f{500.0, 50.0}, 	1.0, sf::Color::Red, 1 )		),
		KeyBinding ( "Right",		sf::Keyboard::D, 		Text( "Right : D", 	sf::Vector2f{500.0, 80.0}, 	1.0, sf::Color::Red, 1 )		),
		KeyBinding ( "Jump", 		sf::Keyboard::Space, 	Text( "Jump : Space", 	sf::Vector2f{500.0, 110.0}, 1.0, sf::Color::Red, 1 ) 	),
		KeyBinding ( "E",			sf::Keyboard::E,		Text( "E : E",		sf::Vector2f{500.0, 150.0}, 1.0, sf::Color::Red, 1)			)
	};

	sf::Event event;
	AssetManager assets;

	Game game(window, assets, bindings);
	Editor editor(window, assets);

	Settings settings(window, assets, bindings);
	Interface interface(game, editor, settings, assets, window);
	StateMachine machine(game, interface, editor, settings);
	
	sf::Clock clock;

	double previous = clock.getElapsedTime().asMilliseconds();
	double lag = 0.0;
	double simulationSpeed = 4;

	while (window.isOpen()){
		double current = clock.getElapsedTime().asMilliseconds();
		double elapsed = current - previous;
		previous = current;
		lag += elapsed;

		while(window.pollEvent(event)){
			if( event.type == sf::Event::Closed ){
				window.close();
			}
			machine.handleEvent(event, view);
		}

		while(lag >= simulationSpeed){
			machine.handleInput(event, view);
			lag -= simulationSpeed;
		}

		window.clear();
		window.setView(view);
		machine.display(event, view);
		window.display();
		//lastFrame = clock.getElapsedTime().asMilliseconds();

		//sf::sleep(sf::milliseconds(5));

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			interface.goToPauseMenu(view);

		}

	}

	return 0;
}

//(1920,1080) (5,3) (1,1) (1,0) | (0,0) (1,2) | idle | waterBubble