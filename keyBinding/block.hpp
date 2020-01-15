#ifndef _BLOCK_HPP
#define _BLOCK_HPP

#include <SFML/Graphics.hpp>

class Block {
private:
	sf::Vector2f position;
	sf::Vector2f size;
	sf::Color color;
	sf::RectangleShape rectangle;

public:

	Block( sf::Vector2f position, sf::Vector2f size = sf::Vector2f{ 30.0, 50.0 }, sf::Color color = { 50, 150, 50 } );

	void draw( sf::RenderWindow & window );

	void move( sf::Vector2f delta );

	bool contains( const sf::Vector2f& object ) const;

	sf::Vector2f castToF( sf::Vector2i target ){
	return sf::Vector2f(
			static_cast<float>( target.x ),
			static_cast<float>( target.y )
		);
	}

};

#endif
