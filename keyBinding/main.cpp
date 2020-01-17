#include <iostream>
#include <SFML/Graphics.hpp>
#include <array>
#include "cScreen.hpp"
#include "menuScreen.hpp"
#include "settingsScreen.hpp"
#include "playScreen.hpp"

int main( int argc, char *argv[] ){
	std::cout << "Starting application 01-05 array of actions\n";

	std::array< cScreen*, 3 > Screens;
	int screen = 0;

	sf::RenderWindow window{ sf::VideoMode{ 640, 480 }, "SFML window" };

	MenuScreen menu;
	SettingsScreen settings;
	PlayScreen play;

	Screens[0] = &menu;
	Screens[1] = &play;
	Screens[2] = &settings;

	while( screen >= 0 ){
		screen = Screens[screen]->Run( window );
	}

	std::cout << "Terminating application\n";
	return 0;
}


