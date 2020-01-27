#include <SFML/Graphics.hpp>
#include "tekst.hpp"
#include <iostream>

Text::Text( std::string input, sf::Vector2f position, float size, sf::Color color, bool centered ) :
	input{ input },
	position{ position },
	size{ sf::Vector2f{size, size} },
	color{ color },
	centered{ centered }
{
	if (!font.loadFromFile("OpenSans-Italic.ttf")){}
	text.setOutlineThickness(1);
	text.setOutlineColor(sf::Color::Green);
}

void Text::draw( sf::RenderWindow & window ) {
	text.setFont(font);
	text.setString(input);
	text.setScale(size);

	//sets the position as upper center of the object if bool centered is set true
	if(centered && calculated){
		sf::FloatRect object = text.getLocalBounds();
		text.setPosition(sf::Vector2f{position.x - ((object.width - object.left) / 2), position.y });
		calculated = false;
	}

	text.setFillColor(color);
	window.draw(text);
}

void Text::setText( std::string newText ){
	input = newText;
	calculated = true;			//if a new text is set, set the dirty flag to true to redo the calculations
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

void Text::setColor(sf::Color newColor){
	color = newColor;
}

void Text::makeCentered(bool check){
	check ? centered = true : centered = false;
}