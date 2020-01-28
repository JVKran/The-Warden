/// @file

#include "Settings.hpp"


Settings::Settings( sf::RenderWindow & window, AssetManager & assets, std::vector<KeyBinding> & bindings ):
	window( window ),
	bindings(bindings),
	action(Action([]{})),
	world(assets)
	{
			world.loadWorld("Interface/backgroundWorld.txt");

		//background.setTexture(assets.getTexture("background"));
	}

void Settings::initialize(StateMachine * machine){
	
	 action = Action( [machine]{  machine->changeState(std::make_shared<MenuState>());});
}

void Settings::handleInput(){

	switch(state){
		case StateSettings::IDLE: {
			//change the color to blue of the Binding object if the mouse is on it else make it red 
			for( auto & key : bindings ){
				key.contains( sf::Mouse::getPosition(window)) ? key.setColor( sf::Color::White ) : key.setColor( sf::Color::Black );
			}

			//change the color of backButton to blue if the mouse is on it else make it red
			backButton.contains( sf::Mouse::getPosition(window)) ? backButton.setColor( sf::Color::White ) : backButton.setColor( sf::Color::Black );
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
					action.startFunction();
				}else{
					uint counter = 0;												//holds the index of Bindings object (see uint selectedKey)
					for( KeyBinding & keyRef : bindings ){
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
				for( KeyBinding & keyRef : bindings ){
					if(event.key.code == keyRef.getKey()){		//sets usedKey true if key already in key objects
						usedKey = true;
					}
				}
				//seperate keyboard::A check because event.key.code won't give a 0 if the key is A
				if( event.key.code == sf::Keyboard::A && !usedKey){		//in case of key A and usedKey = false, set the new key A and go to state Idle
					bindings[selectedKey].setKey(sf::Keyboard::A);
					state = StateSettings::IDLE;
				}else if(event.key.code && !usedKey){					//in any other key case just check if usedKey = false and change the key to the new key and go to state Idle
					bindings[selectedKey].setKey(event.key.code);
					state = StateSettings::IDLE;
				}
			}else if( sf::Mouse::isButtonPressed(sf::Mouse::Left) ){	//if the left mouse button is pressed go back to state Idle
				state = StateSettings::IDLE;
			}

			break;		
		}
	}
}

void Settings::draw(sf::View & view){
	sf::Vector2f position = view.getCenter() - (view.getSize()/2.0f);
	settingBackground.setPosition(position.x+800,position.y+50);
	settingBackground.setFillColor(sf::Color(230,157,32));
	settingBackground.setSize(sf::Vector2f(300,400));


	for(uint_fast8_t windowLayer = 0; windowLayer <= 4; windowLayer ++){
			world.draw(window, view, windowLayer);				// Finaly, draw one more layer that's also able to draw over Characters.
		}
	window.draw(settingBackground);
	for( auto & p : bindings ){
		p.draw( window );				//all the key objects
	}

	backButton.draw( window );			//backbutton object
}
