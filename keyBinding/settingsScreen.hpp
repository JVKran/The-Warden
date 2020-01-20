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
	uint selectedKey = 0;			//holds the index of the array Bindings, needed to select a key if pressed on it

	Text backButton = { "Back", sf::Vector2f{50.0, 440.0}, 1.0, sf::Color::Red};		//seperate backButton object for going back to menu screen

	while ( Running ){

		while( window.pollEvent(event) ){

			switch(state){
				case State::IDLE: {		//default state

					//change the color to blue of the Binding object if the mouse is on it else make it red 
					for( auto & key : Bindings ){
						key.contains( sf::Mouse::getPosition(window)) ? key.setColor( sf::Color::Blue ) : key.setColor( sf::Color::Red );
					}

					//change the color of backButton to blue if the mouse is on it else make it red
					backButton.contains( sf::Mouse::getPosition(window)) ? backButton.setColor( sf::Color::Blue ) : backButton.setColor( sf::Color::Red );

					if( event.type == sf::Event::Closed ){				//close window if cross button is pressed
						return -1;
					}else if( sf::Keyboard::isKeyPressed(sf::Keyboard::Escape )){		//returns to the menu screen
						return 0;
					}else if( sf::Mouse::isButtonPressed(sf::Mouse::Left) ){			
						if( backButton.contains( sf::Mouse::getPosition(window)) ){		//if backButton is pressed go back to menu screen
							return 0;
						}else{
							uint counter = 0;												//holds the index of Bindings object (see uint selectedKey)
							for( KeyBinding & keyRef : Bindings ){
								if( keyRef.contains( sf::Mouse::getPosition(window)) ){		//if mouse is pressed on Bindings object set blue color and go to the state CHANGEKEY
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
				case State::CHANGEKEY: {		//state if one of the Bindings objects is pressed
					if( event.type == sf::Event::Closed ){				//close window if cross button is pressed
						return -1;
					}else if( event.type == sf::Event::KeyPressed ){	//checks if a key on the keyboard is pressed
						bool usedKey = false;							//flag to check if a key already is used by another key object
						for( KeyBinding & keyRef : Bindings ){
							if(event.key.code == keyRef.getKey()){		//sets usedKey true if key already in key objects
								usedKey = true;

							}
						}
						//seperate keyboard::A check because event.key.code won't give a 0 if the key is A
						if( event.key.code == sf::Keyboard::A && !usedKey){		//in case of key A and usedKey = false, set the new key A and go to state Idle
							Bindings[selectedKey].setKey(sf::Keyboard::A);
							state = State::IDLE;
						}else if(event.key.code && !usedKey){					//in any other key case just check if usedKey = false and change the key to the new key and go to state Idle
							Bindings[selectedKey].setKey(event.key.code);
							state = State::IDLE;
						}
					}else if( sf::Mouse::isButtonPressed(sf::Mouse::Left) ){	//if the left mouse button is pressed go back to state Idle
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

	return -1;		//returns -1 if something goes wrong

}

#endif
