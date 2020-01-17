#include "FactoryFunction.hpp"
#include "../exceptions.hpp"

std::ifstream & operator>>( std::ifstream & input, sf::Vector2f & rhs ){
	char c;
	if(!( input >> c )){ 
		throw endOfFile(); 
	}
	if(c != '('){ 
		throw invalidPosition( c ); 
	}
	if(!(input >> rhs.x)){
		input.clear();
		throw invalidPosition( c );
	}
	if(!(input >> c)) {
        throw endOfFile();
    }
    if(!(input >> rhs.y)){
    	input.clear();
		throw invalidPosition( c );
    }
    if(!(input >> c)) {
        throw endOfFile();
    }
	if(c != ')'){
		throw invalidPosition( c ); 
	}
	return input;
}

std::ifstream & operator>>( std::ifstream & input, sf::Vector2i & rhs ){
	char c;
	if(!( input >> c )){ 
		throw endOfFile(); 
	}
	if(c != '('){ 
		throw invalidPosition( c ); 
	}
	if(!(input >> rhs.x)){
		input.clear();
		throw invalidPosition( c );
	}
	if(!(input >> c)) {
        throw endOfFile();
    }
    if(!(input >> rhs.y)){
    	input.clear();
		throw invalidPosition( c );
    }
    if(!(input >> c)) {
        throw endOfFile();
    }
	if(c != ')'){
		throw invalidPosition( c ); 
	}
	return input;
}