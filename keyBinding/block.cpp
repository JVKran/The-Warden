#include <SFML/Graphics.hpp>
#include "block.hpp"

Block::Block( sf::Vector2f position, sf::Vector2f size, sf::Color color ) :
	position{ position },
	size{ size },
	color{ color }
{}

void Block::draw( sf::RenderWindow & window ) {
	rectangle.setSize(size);
	rectangle.setPosition(position);
	rectangle.setFillColor(color);
	window.draw(rectangle);
}

void Block::move( sf::Vector2f delta ){
	position += delta;
}

bool Block::contains( const sf::Vector2f& object ) const {
	return rectangle.getGlobalBounds().contains( object );
}
