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

	Text( std::string input, sf::Vector2f position, float size = 1.0, sf::Color color = sf::Color::Black );

	void draw( sf::RenderWindow & window );

	void setText( std::string newText );

	std::string getText();

	bool contains( const sf::Vector2f& object ) const;

	bool contains( const sf::Vector2i& object );

	sf::Vector2f castToF( sf::Vector2i target ){
		return sf::Vector2f(
			static_cast<float>( target.x ),
			static_cast<float>( target.y )
		);
	}

};

#endif