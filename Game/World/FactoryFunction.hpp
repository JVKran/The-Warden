#ifndef __FACTORY_FUNCTION_HPP
#define __FACTORY_FUNCTION_HPP

#include <fstream>
#include <SFML/Graphics.hpp>

std::ifstream & operator>>( std::ifstream & input, sf::Vector2f & rhs );

std::ifstream & operator>>( std::ifstream & input, sf::Vector2i & rhs );

#endif