#ifndef _PLAYSCREEN_HPP
#define _PLAYSCREEN_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "cScreen.hpp"
#include "block.hpp"
#include "action.hpp"
#include "keybinding.hpp"
#include  "tekst.hpp"
#include "bindings.hpp"

class PlayScreen : public cScreen {
private:
	bool playing;
	Block player = {sf::Vector2f{180.0, 50.0}, sf::Vector2f{20.0, 20.0}};

public:
	PlayScreen(void);
	virtual int Run( sf::RenderWindow & window );
};

PlayScreen::PlayScreen(void){
	playing = false;
}

int PlayScreen::Run( sf::RenderWindow & window ){
	sf::Event event;
	bool Running = true;

	std::array< Action, 4 > actions = {
		Action( Bindings[0].getKey(),  [&](){ player.move( sf::Vector2f( -1.0,  0.0 )); 	}),
		Action( Bindings[1].getKey(),  [&](){ player.move( sf::Vector2f( +1.0,  0.0 )); 	}),
		Action( Bindings[2].getKey(),  [&](){ player.move( sf::Vector2f(  0.0, -1.0 )); 	}),
		Action( Bindings[3].getKey(),  [&](){ player.move( sf::Vector2f(  0.0, +1.0 )); 	})
	};

	while ( Running ){

		while( window.pollEvent(event) ){
			if (event.type == sf::Event::Closed){
				return -1;
			}else if(event.type == sf::Event::KeyPressed){
				if(event.key.code == sf::Keyboard::Escape){
					return 0;
				}
			}
		}

		for( auto & action : actions ){
			action();
		}

		window.clear();

		player.draw( window );

		window.display();

		sf::sleep( sf::milliseconds( 2 ));
	}

	return -1;

}

#endif
