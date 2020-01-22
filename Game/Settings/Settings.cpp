/// @file

#include "Settings.hpp"

Settings::Settings( sf::RenderWindow & window, AssetManager & assets ):
	window( window )
{
		background.setTexture(assets.getTexture("background"));

}

void Settings::initialize(StateMachine * machine){
	
	elements = InterfaceElement( Action ( [machine]{  machine->changeState(std::make_shared<MenuState>());}));

}

void Settings::handleInput(){

	switch(state){
		case StateSettings::IDLE: {
			//change the color to blue of the Binding object if the mouse is on it else make it red 
			for( auto & key : Bindings ){
				key.contains( sf::Mouse::getPosition(window)) ? key.setColor( sf::Color::Blue ) : key.setColor( sf::Color::Red );
			}

			//change the color of backButton to blue if the mouse is on it else make it red
			backButton.contains( sf::Mouse::getPosition(window)) ? backButton.setColor( sf::Color::Blue ) : backButton.setColor( sf::Color::Red );
			break;
		}
		case StateSettings::CHANGEKEY: {
			break;
		}
	}
}

void Settings::handleEvent( const sf::Event & event ){									

	switch(state){
		case StateSettings::IDLE: {		//default state

			if( sf::Mouse::isButtonPressed(sf::Mouse::Left) ){			
				if( backButton.contains( sf::Mouse::getPosition(window)) ){		//if backButton is pressed go back to menu screen
					element.changeState();
				}else{
					uint counter = 0;												//holds the index of Bindings object (see uint selectedKey)
					for( KeyBinding & keyRef : Bindings ){
						if( keyRef.contains( sf::Mouse::getPosition(window)) ){		//if mouse is pressed on Bindings object set blue color and go to the state CHANGEKEY
							keyRef.setColor( sf::Color::Blue );
							selectedKey = counter;
							state = StateSettings::CHANGEKEY;
						}
						counter++;
					}
				}
			}	

			break;
		}
		case StateSettings::CHANGEKEY: {		//state if one of the Bindings objects is pressed
			if( event.type == sf::Event::KeyPressed ){	//checks if a key on the keyboard is pressed
				bool usedKey = false;							//flag to check if a key already is used by another key object
				for( KeyBinding & keyRef : Bindings ){
					if(event.key.code == keyRef.getKey()){		//sets usedKey true if key already in key objects
						usedKey = true;
					}
				}
				//seperate keyboard::A check because event.key.code won't give a 0 if the key is A
				if( event.key.code == sf::Keyboard::A && !usedKey){		//in case of key A and usedKey = false, set the new key A and go to state Idle
					Bindings[selectedKey].setKey(sf::Keyboard::A);
					state = StateSettings::IDLE;
				}else if(event.key.code && !usedKey){					//in any other key case just check if usedKey = false and change the key to the new key and go to state Idle
					Bindings[selectedKey].setKey(event.key.code);
					state = StateSettings::IDLE;
				}
			}else if( sf::Mouse::isButtonPressed(sf::Mouse::Left) ){	//if the left mouse button is pressed go back to state Idle
				state = StateSettings::IDLE;
			}

			break;		
		}
	}
}

void Settings::draw(){
	window.draw(background);
	for( auto & p : Bindings ){
		p.draw( window );				//all the key objects
	}

	backButton.draw( window );			//backbutton object
}
