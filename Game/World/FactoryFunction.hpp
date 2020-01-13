#ifndef __FACTORY_FUNCTION_HPP
#define __FACTORY_FUNCTION_HPP

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

#endif