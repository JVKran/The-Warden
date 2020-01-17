#include <SFML/Graphics.hpp>
#include "tekst.hpp"

Text::Text( std::string input, sf::Vector2f position, float size, sf::Color color ) :
	input{ input },
	position{ position },
	size{ sf::Vector2f{size, size} },
	color{ color }
{
	if (!font.loadFromFile("OpenSans-Italic.ttf")){}
}

void Text::draw( sf::RenderWindow & window ) {
	text.setFont(font);
	text.setString(input);
	text.setScale(size);
	text.setPosition(position);
	text.setFillColor(color);
	window.draw(text);
}

void Text::setText( std::string newText ){
	input = newText;
}

std::string Text::getText(){
	return input;
}

bool Text::contains( const sf::Vector2f& object ) const {
	return text.getGlobalBounds().contains( object );
}