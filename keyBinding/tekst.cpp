#include <SFML/Graphics.hpp>
#include "tekst.hpp"
#include <iostream>

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

	if(calculated){
		sf::FloatRect object = text.getLocalBounds();
		text.setPosition(sf::Vector2f{position.x - ((object.width - object.left) / 2), position.y });
		calculated = false;
	}

	text.setFillColor(color);
	window.draw(text);
}

void Text::setText( std::string newText ){
	input = newText;
	calculated = true;
}

std::string Text::getText(){
	return input;
}

bool Text::contains( const sf::Vector2f& object ) const {
	return text.getGlobalBounds().contains( object );
}

bool Text::contains( const sf::Vector2i& object ){
	return text.getGlobalBounds().contains( castToF(object) );
}