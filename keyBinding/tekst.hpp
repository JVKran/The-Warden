#ifndef _TEKST_HPP
#define _TEKST_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Text {
private:
	std::string input;
	sf::Vector2f position;
	sf::Vector2f size;
	sf::Color color;
	sf::Text text;
	sf::Font font;

public:

	Text( std::string input, sf::Vector2f position, sf::Vector2f size = sf::Vector2f{1.0, 1.0}, sf::Color color = sf::Color::Black );

	void draw( sf::RenderWindow & window );

	void setText( std::string newText );

	std::string getText();

};

#endif
