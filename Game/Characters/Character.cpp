#include "Character.hpp"

void PlayerPhysics::processPhysics(World & world, sf::Vector2f & position){
	//Refrence naar view bij world vandaan halen
	//View.move(sf::Vector2f(newpos.x, 0));
}

void PlayerInput::processInput(sf::Vector2f & velocity){
	//Set velocity
	//Set animations
}

void Character::update(sf::RenderWindow & window, World & world){
	input.processInput(velocity);
	physics.processPhysics(world, position);
};

void attack(){
	
}