#ifndef _SETTINGSSCREEN_HPP
#define _SETTINGSSCREEN_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>

#include "cScreen.hpp"
#include "action.hpp"
#include "tekst.hpp"
#include "bindings.hpp"

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

	Text backButton = { "Back", sf::Vector2f{50.0, 440.0}, 1.0, sf::Color::Red};

	while ( Running ){

		while( window.pollEvent(event) ){
			if (event.type == sf::Event::Closed){
				return -1;
			}else if(event.type == sf::Event::KeyPressed){

				if(event.key.code == sf::Keyboard::Escape){
					return 0;
				}else if(event.key.code == sf::Keyboard::P){
					Bindings[0].setKey(event.key.code);
				}

			}else if( event.type == sf::Event::MouseButtonPressed){

				if (event.mouseButton.button == sf::Mouse::Left){
					if(backButton.contains( sf::Mouse::getPosition(window))){
						return 0;
					}else{
						for( auto & p : Bindings ){
							if(p.contains( sf::Mouse::getPosition(window))){
								bool check = true;
								while(check){

									sf::sleep( sf::milliseconds( 10 ));

									while( window.pollEvent(event)){
										if(event.type == sf::Event::KeyPressed){
											if(event.key.code == sf::Keyboard::A){
												p.setKey(sf::Keyboard::A);
												check = false;
											}else{
												p.setKey(event.key.code);
												check = false;
											}
										}else if( event.type == sf::Event::MouseButtonPressed){
											if (event.mouseButton.button == sf::Mouse::Left){
												check = false;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}

		window.clear();

		for( auto & p : Bindings ){
			p.draw( window );
		}

		backButton.draw( window );

		window.display();

		sf::sleep( sf::milliseconds( 10 ));
	}

	return -1;

}

#endif
