#include <iostream>
#include <SFML/Graphics.hpp>
#include "action.hpp"
#include "block.hpp"
#include <array>
#include "tekst.hpp"
#include "keybinding.hpp"

int main( int argc, char *argv[] ){
	std::cout << "Starting application 01-05 array of actions\n";

	sf::RenderWindow window{ sf::VideoMode{ 640, 480 }, "SFML window" };

	Block player = {sf::Vector2f{180.0, 50.0}, sf::Vector2f{20.0, 20.0}};

	KeyBinding keyBinding[] = {
		KeyBinding("backward", 	sf::Keyboard::A, Block(sf::Vector2f{50.0, 50.0}, sf::Vector2f{100.0, 20.0}),  Text("backward : A", sf::Vector2f{53.0, 50.0},  sf::Vector2f{0.5, 0.5})),
		KeyBinding("forward", 	sf::Keyboard::D, Block(sf::Vector2f{50.0, 80.0}, sf::Vector2f{100.0, 20.0}),  Text("forward : D", sf::Vector2f{53.0, 80.0},  sf::Vector2f{0.5, 0.5})),
		KeyBinding("up", 		sf::Keyboard::W, Block(sf::Vector2f{50.0, 110.0}, sf::Vector2f{100.0, 20.0}), Text("up : W", sf::Vector2f{53.0, 110.0}, sf::Vector2f{0.5, 0.5})),
		KeyBinding("down", 		sf::Keyboard::S, Block(sf::Vector2f{50.0, 140.0}, sf::Vector2f{100.0, 20.0}), Text("down : S", sf::Vector2f{53.0, 140.0}, sf::Vector2f{0.5, 0.5}))
	};

	Action actions[] = {
		Action( keyBinding[0].getKey(),  	[&](){ player.move( sf::Vector2f( -1.0,  0.0 )); }),
		Action( keyBinding[1].getKey(), 	[&](){ player.move( sf::Vector2f( +1.0,  0.0 )); }),
		Action( keyBinding[2].getKey(),   	[&](){ player.move( sf::Vector2f(  0.0, -1.0 )); }),
		Action( keyBinding[3].getKey(),  	[&](){ player.move( sf::Vector2f(  0.0, +1.0 )); }),
		Action(sf::Mouse::Left, 			[&](){uint i = 0; bool check = 1; for(auto & p : keyBinding){
																if(p.contains( p.castToF(sf::Mouse::getPosition(window)))){ 
																	while(check){
																		sf::Event event; 
																		while(window.pollEvent(event)){ 
																			if (event.type == sf::Event::KeyPressed){ 
																			p.setKey(event.key.code); 
																			actions[i].changeCondition(p.getKey());
																			check = 0;
																			}
																		} 
																	}
																}	 
															  i++; 
															  }
															})
	};

	while (window.isOpen()) {
		for( auto & action : actions ){
			action();
		}

		window.clear();

		for( auto & p : keyBinding){
			p.draw( window );
		}

        player.draw( window );

		window.display();

		sf::sleep( sf::milliseconds( 10 ));

        sf::Event event;		
	    while( window.pollEvent(event) ){
			if( event.type == sf::Event::Closed ){
				window.close();
			}
		}
	}

	std::cout << "Terminating application\n";
	return 0;
}


