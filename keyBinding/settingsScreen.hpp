#ifndef _SETTINGSSCREEN_HPP
#define _SETTINGSSCREEN_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "cScreen.hpp"
#include "block.hpp"
#include "action.hpp"

class SettingsScreen : public cScreen {
private:
	bool playing;

public:
	SettingsScreen(void);
	virtual int Run( sf::RenderWindow & window );

};

SettingsScreen::SettingsScreen(void){
	playing = false;
}

int SettingsScreen::Run( sf::RenderWindow & window ){
	sf::Event event;
	bool Running = true;


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

		window.clear();

		window.display();

		sf::sleep( sf::milliseconds( 10 ));
	}

	return -1;

}

#endif
