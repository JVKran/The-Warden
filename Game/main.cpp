#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"
#include "World.hpp"
#include "Editor.hpp"
#include "Character.hpp"

int main(){
	#define playmode
	AssetManager assets;
	assets.loadObjects("Assets/objects.txt");

	sf::View view(sf::FloatRect(0.f, 0.f, 1000.f, 580.f));

	#ifdef playmode
	World world(assets, "World/world.txt", view);		//Create world with world.txt as config
	#else
	Editor editor( assets, "World/world.txt", view );	//Edit world world.txt
	#endif
	sf::RenderWindow window{ sf::VideoMode{ 1000, 580 }, "The Warden", sf::Style::Resize};

	sf::Clock clock;
	uint_fast8_t msPerUpdate = 16;
	double previous,  current, elapsed;
	Character speler(sf::Vector2f(500,100),"crate",assets,window);
	window.setVerticalSyncEnabled(0);
	window.setFramerateLimit(60);
	int lag;

	elapsed=0;
// Load the font from a file
sf::Font MyFont;
if (!MyFont.loadFromFile("OpenSans-Bold.ttf"))
{
    // Error...
}

sf::Text text;

// select the font
text.setFont(MyFont); // font is a sf::Font

// set the string to display
text.setString("Hello world");

// set the character size
text.setCharacterSize(24); // in pixels, not points!


text.setFillColor(sf::Color::Red);
text.move(sf::Vector2f(20,20));

	while (window.isOpen()){
		
		//elapsed = current - previous;

		//lag += elapsed;

		// processInput();
		#ifdef playmode
		window.clear();
		world.draw(window);
		window.draw(text);
		speler.update(window, world);		
		window.setView(view);
		#else
				window.clear();
				editor.draw( window );
				window.setView(view);
		#endif
				//sf::sleep( sf::milliseconds( 14 ));
		current = (clock.getElapsedTime().asMilliseconds());
		//std::cout<<"thinktime   "<<float(current-previous)<<'\n';
		lag=0;

		while(current-previous<msPerUpdate){
			lag+=1;
			#ifdef playmode
				window.display();
			#else
				window.display();

			#endif
			//lag -= msPerUpdate;
			current = (clock.getElapsedTime().asMilliseconds());
			//std::cout<<"looptime   "<<float((current-previous))<<"       "<<lag<<'\n';
		}
		//std::cout<<"totalframe   "<<int(1000.f/(current-previous))<<"       "<<lag<<'\n';
		text.setString(std::to_string(1000.f/(current-previous))+"   "+std::to_string(lag));
		
		previous=current;

		#ifndef playmode
			editor.handleInput(window);
		#endif

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			window.close();
		}
			
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)){
			window.setVerticalSyncEnabled(0);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){
			window.setVerticalSyncEnabled(1);
		}

		sf::Event event;		
	    while( window.pollEvent(event) ){
			if( event.type == sf::Event::Closed ){
				window.close();
			}
		}
	//current = (clock.getElapsedTime().asMilliseconds());
	//previous = current;
	}

	#ifndef playmode
	editor.editingDone();
	#endif
	return 0;
}