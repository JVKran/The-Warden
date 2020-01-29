/// @file
#ifndef _ACTION_HPP
#define _ACTION_HPP

#include <functional>
#include <SFML/Graphics.hpp>
/// \brief
/// Action
/// \details
/// This will handle the given lambda function.
class Action {
private:
	std::function< void() > work;
public:
	Action( std::function< void() > work) :  
		work( work ) 
	{}
	/// \brief
	/// Start lambda.
	/// \details
	/// This function will start the given lambda function.
	void startFunction(){ work(); }
	
};

#endif