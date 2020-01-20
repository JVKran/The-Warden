#ifndef _SETTINGSSCREEN_HPP
#define _SETTINGSSCREEN_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>

#include "cScreen.hpp"
#include "action.hpp"
#include "tekst.hpp"
#include "bindings.hpp"
#include "keybinding.hpp"

enum class State
{
    IDLE,
    CHANGEKEY
};

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
	State state = State::IDLE;
	bool Running = true;
	uint selectedKey = 0;

	Text backButton = { "Back", sf::Vector2f{50.0, 440.0}, 1.0, sf::Color::Red};

	while ( Running ){

		while( window.pollEvent(event) ){

			switch(state){
				case State::IDLE: {

					for( auto & key : Bindings ){
						key.contains( sf::Mouse::getPosition(window)) ? key.setColor( sf::Color::Blue ) : key.setColor( sf::Color::Red );
					}

					backButton.contains( sf::Mouse::getPosition(window)) ? backButton.setColor( sf::Color::Blue ) : backButton.setColor( sf::Color::Red );

					if( event.type == sf::Event::Closed ){
						return -1;
					}else if( sf::Keyboard::isKeyPressed(sf::Keyboard::Escape )){
						return 0;
					}else if( sf::Mouse::isButtonPressed(sf::Mouse::Left) ){
						if( backButton.contains( sf::Mouse::getPosition(window)) ){
							return 0;
						}else{
							uint counter = 0;
							for( KeyBinding & keyRef : Bindings ){
								if( keyRef.contains( sf::Mouse::getPosition(window)) ){
									keyRef.setColor( sf::Color::Blue );
									selectedKey = counter;
									state = State::CHANGEKEY;
								}
								counter++;
							}
						}
					}			

					break;
				}
				case State::CHANGEKEY: {
					if( event.type == sf::Event::Closed ){
						return -1;
					}else if( event.type == sf::Event::KeyPressed ){
						bool usedKey = false;
						for( KeyBinding & keyRef : Bindings ){
							if(event.key.code == keyRef.getKey()){
								usedKey = true;

							}
						}
						if( event.key.code == sf::Keyboard::A && !usedKey){
							Bindings[selectedKey].setKey(sf::Keyboard::A);
							state = State::IDLE;
						}else if(event.key.code && !usedKey){
							Bindings[selectedKey].setKey(event.key.code);
							state = State::IDLE;
						}
					}else if( sf::Mouse::isButtonPressed(sf::Mouse::Left) ){
						state = State::IDLE;
					}

					break;
				}

			}
		}

		window.clear();

		for( auto & p : Bindings ){
			p.draw( window );
		}

		backButton.draw( window );

		window.display();

		sf::sleep( sf::milliseconds( 20 ));
	}

	return -1;

}

#endif
