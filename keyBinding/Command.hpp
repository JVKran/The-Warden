#ifndef _COMMAND_HPP
#define _COMMAND_HPP

#include <SFML/Graphics.hpp>

class Command {
private:
	

public:

	Command( sf::Vector2f position, sf::Vector2f size = sf::Vector2f{ 30.0, 50.0 }, sf::Color color = { 50, 150, 50 } );

	void execute(){
		
	}

};

#endif
