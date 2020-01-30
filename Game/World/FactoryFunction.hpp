#ifndef __FACTORY_FUNCTION_HPP
#define __FACTORY_FUNCTION_HPP

#include <fstream>
#include <SFML/Graphics.hpp>
#include "Exceptions.hpp"

/// \brief
/// Read sf::Vector2f from ifstream
/// \details
/// This function reads one single sf::Vector2f from the ifstream into the passed parameter.
/// Used for reading the position from the world configuration file.
/// @param input The std::ifstream to read from.
/// @param rhs The sf::Vector2f to read the vector into.
/// \return  The std::ifstream to pass the rest of the std::ifstream into.
/// \exception endOfFile() The passes std::ifstream object leads to an EOF marker.
/// \exception invalidPosition() The syntax of the read string position is not right.
std::ifstream & operator>>( std::ifstream & input, sf::Vector2f & rhs );

/// \brief
/// Read sf::Vector2i from ifstream
/// \details
/// This function reads one single sf::Vector2i from the ifstream into the passed parameter.
/// Used for reading the position from the world configuration file.
/// @param input The std::ifstream to read from.
/// @param rhs The sf::Vector2i to read the vector into.
/// \return  The std::ifstream to pass the rest of the std::ifstream into.
/// \exception endOfFile() The passes std::ifstream object leads to an EOF marker.
/// \exception invalidPosition() The syntax of the read string position is not right.
std::ifstream & operator>>( std::ifstream & input, sf::Vector2i & rhs );

/// \brief
/// Is file empty?
/// \details
/// Used instead of std::eof() since eof() checks if the last read operation contained an EOF. 
/// That's not what we want; we want to know wether the next operation will be an EOF.
/// @param file The std::ifstream object to determine for wether there's an EOF or not.
/// \return Wether or not the passed std::ifstream is empty or not.
bool isEmpty(std::ifstream & file);

/// \brief
/// sf::Vector2f to string
/// \details
/// This function converts its parameter to a string. Used for storing the position
/// in the world configuration file.
/// \return The passed sf::Vector2f in string format.
std::string getPositionString(const sf::Vector2f & positionToPrint);

#endif //__FACTORY_FUNCTION_HPP