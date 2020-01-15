#ifndef _ACTION_HPP
#define _ACTION_HPP

#include <functional>
#include <SFML/Graphics.hpp>

class Action {
private:
	std::function< bool() > condition;
	std::function< void() > work;
public:
	Action(
	   std::function< bool() > condition, 
	   std::function< void() > work
	) : condition( condition ), 
		work( work ) 
	{}

	Action(
		sf::Keyboard::Key key,
		std::function< void() > work
	) :
		condition(
			[ key ]()->bool { return sf::Keyboard::isKeyPressed( key ); }
		),
		work(work)
	{}

	Action(
		sf::Mouse::Button button,
		std::function< void() > work
	) :
		condition(
			[ button ]()->bool { return sf::Mouse::isButtonPressed( button ); }
		),
		work(work)
	{}

	void changeCondition(sf::Keyboard::Key newKey ){
		condition = [ newKey ]()->bool { return sf::Keyboard::isKeyPressed( newKey ); };
	}

	void operator()(){
		if( condition() ){
			work();
		}
	}
};

#endif