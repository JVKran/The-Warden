#ifndef _ACTION_HPP
#define _ACTION_HPP

#include <functional>
#include <SFML/Graphics.hpp>

class Action {
private:
	std::function< void() > work;
public:
	Action( std::function< void() > work) :  
		work( work ) 
	{}

	void startFunction(){ work(); }
	
};

#endif