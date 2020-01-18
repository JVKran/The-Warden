#ifndef __FACTORY_FUNCTION_HPP
#define __FACTORY_FUNCTION_HPP

#include <fstream>
#include <SFML/Graphics.hpp>
#include "Exceptions.hpp"

std::ifstream & operator>>( std::ifstream & input, sf::Vector2f & rhs );
std::ifstream & operator>>( std::ifstream & input, sf::Vector2i & rhs );

bool isEmpty(std::ifstream & file);
std::string getPositionString(const sf::Vector2f & positionToPrint);

#endif //__FACTORY_FUNCTION_HPP