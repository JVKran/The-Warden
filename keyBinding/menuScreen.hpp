#ifndef _MENUSCREEN_HPP
#define _MENUSCREEN_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "cScreen.hpp"
#include "block.hpp"
#include "action.hpp"
#include <array>
#include "tekst.hpp"

class MenuScreen : public cScreen {
private:
	bool playing;

public:
	MenuScreen(void);
	virtual int Run( sf::RenderWindow & window );

};

MenuScreen::MenuScreen(void){
	playing = false;
}

int MenuScreen::Run( sf::RenderWindow & window ){
	sf::Event event;
	bool Running = true;

	//text objects that serve as button objects to go to the right screen
	std::array<Text, 3> objects = {
		Text( "Play", 		sf::Vector2f{320.0, 50.0},   1.0, sf::Color::Red, 1),
		Text( "Settings", 	sf::Vector2f{320.0, 100.0},  1.0, sf::Color::Red, 1),
		Text( "Exit", 		sf::Vector2f{320.0, 150.0},  1.0, sf::Color::Red, 1)
	};

	while ( Running ){

		//make a text object blue if mouse is on it else make it red
		for( auto & p : objects ){
			if(p.contains( sf::Mouse::getPosition(window))){
				p.setColor( sf::Color::Blue );	
			}else{
				p.setColor( sf::Color::Red );
			}
		}

		while( window.pollEvent(event) ){
			if (event.type == sf::Event::Closed){
				return -1;
			}else if( event.type == sf::Event::MouseButtonPressed){
				if (event.mouseButton.button == sf::Mouse::Left){						
					if(objects[0].contains( sf::Mouse::getPosition(window))){ 			//if mouse is pressed on object[0] go to playScreen
						return 1; 
					}else if(objects[1].contains(sf::Mouse::getPosition(window))){		//if mouse is pressed on object[1] go to settingsScreen 
						return 2; 
					}else if(objects[2].contains(sf::Mouse::getPosition(window))){		//if mouse is pressed on object[2] exit the game
						return -1;
					}

				}
			}
		}


		window.clear();

		for( auto & p : objects ){
			p.draw( window );
		}

		window.display();

		sf::sleep( sf::milliseconds( 10 ));
	}

	return -1;

}

#endif
