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
		KeyBinding ( "Left", 					sf::Keyboard::A,  		Text( "Left : A", 							sf::Vector2f{960.0, 40.0}, 	 1, sf::Color::Black, 1 )),
		KeyBinding ( "Right",					sf::Keyboard::D, 		Text( "Right : D", 							sf::Vector2f{960.0, 80.0},  1, sf::Color::Black, 1 )),
		KeyBinding ( "Jump", 					sf::Keyboard::Space, 	Text( "Jump : Space", 						sf::Vector2f{960.0, 120.0},  1, sf::Color::Black, 1 )),
		KeyBinding ( "Use",						sf::Keyboard::E,		Text( "Use : E",							sf::Vector2f{960.0, 160.0},  1, sf::Color::Black, 1 )),
		KeyBinding ( "Delete",					sf::Keyboard::Delete,	Text( "Delete : Delete",					sf::Vector2f{960.0, 200.0},  1, sf::Color::Black, 1 )),
		KeyBinding ( "Set collidable",			sf::Keyboard::LBracket,	Text( "Set collidable : LBracket",			sf::Vector2f{960.0, 240.0},  1, sf::Color::Black, 1 )),
		KeyBinding ( "Unset collidable",		sf::Keyboard::RBracket,	Text( "Unset collidable : RBracket",		sf::Vector2f{960.0, 280.0},  1, sf::Color::Black, 1 )),
		KeyBinding ( "Set Layer 0",				sf::Keyboard::F1,		Text( "Set Layer 0 : F1",					sf::Vector2f{960.0, 320.0},  1, sf::Color::Black, 1 )),
		KeyBinding ( "Set Layer 1",				sf::Keyboard::F2,		Text( "Set Layer 1 : F2",					sf::Vector2f{960.0, 360.0},  1, sf::Color::Black, 1 )),
		KeyBinding ( "Set Layer 2",				sf::Keyboard::F3,		Text( "Set Layer 2 : F3",					sf::Vector2f{960.0, 400.0},  1, sf::Color::Black, 1 )),
		KeyBinding ( "Set Layer 3",				sf::Keyboard::F4,		Text( "Set Layer 3 : F4",					sf::Vector2f{960.0, 440.0},  1, sf::Color::Black, 1 )),
		KeyBinding ( "Set Layer 4",				sf::Keyboard::F5,		Text( "Set Layer 4 : F5",					sf::Vector2f{960.0, 480.0},  1, sf::Color::Black, 1 )),
		KeyBinding ( "Set interactable",		sf::Keyboard::N,		Text( "Set interactable : N",				sf::Vector2f{960.0, 520.0},  1, sf::Color::Black, 1 )),
		KeyBinding ( "Change selected item",	sf::Keyboard::LControl,	Text( "change selected item : LControl",	sf::Vector2f{960.0, 560.0}, 1, sf::Color::Black, 1 )),
		KeyBinding ( "Set teleport position",	sf::Keyboard::I, 		Text( "set teleport position : I",			sf::Vector2f{960.0, 600.0}, 1, sf::Color::Black, 1 )),
		KeyBinding ( "Enable vision control",	sf::Keyboard::RControl,	Text( "Enable vision control: RControl",	sf::Vector2f{960.0, 640.0}, 1, sf::Color::Black, 1 )),
		KeyBinding ( "Disable vision control",	sf::Keyboard::J,		Text( "Disable vision control: J",			sf::Vector2f{960.0, 680.0}, 1, sf::Color::Black, 1 ))
	};

	sf::Event event;
	AssetManager assets;

	Game game(window, assets, bindings, event, view);
	Editor editor(window, assets, bindings);

	Settings settings(window, assets, bindings);
	Interface interface(game, editor, settings, assets, window);
	StateMachine machine(game, interface, editor, settings, view);
	
	sf::Clock clock;

	double previous = clock.getElapsedTime().asMilliseconds();
	double lag = 0.0;
	double simulationSpeed = 4;

	while (window.isOpen()){
		double current = clock.getElapsedTime().asMilliseconds();
		double elapsed = current - previous;
		previous = current;
		lag += elapsed;

		if(machine.getCurrentState()->getName() != 4){			//Playing
			while(lag >= simulationSpeed){
				machine.handleInput(event);
				lag -= simulationSpeed;
			}	
		} else {
			machine.handleInput(event);							//Editing
		}		


		window.clear();
		window.setView(view);
		machine.display(event);
		window.display();
		
		while(window.pollEvent(event)){
			if( event.type == sf::Event::Closed ){
				window.close();
			}
			machine.handleEvent(event);
		}


	}
	return 0;
}

//(1920,1080) (5,3) (1,1) (1,0) | (0,0) (1,2) | idle | waterBubble