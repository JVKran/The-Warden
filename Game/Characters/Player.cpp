/// @file

#include "Player.hpp"

PlayerGraphics::PlayerGraphics(const std::string & assetName, AssetManager & assets):
	GraphicsComponent(assetName, assets)
{}


void PlayerPhysics::processPhysics(World & world, sf::Vector2f & position, sf::Vector2f & velocity, sf::Vector2f & direction, const sf::Vector2f & dimensions){

	if(clock.getElapsedTime().asMilliseconds() - lastup.asMilliseconds() > 2){

    switch (state){
		case (states::FALLING): {
			if(bottomCollision){
				state = states::STANDING;
				velocity.y = 0;
			} else {
				if(velocity.y < 4){
					velocity.y += 0.09;
				}
			}
			
			break;
		}
		case (states::STANDING):
			if(direction.y < 0){
				state = states::JUMPING;
				velocity.y = -6;
				break;
			}
			if(!bottomCollision){
				state = states::FALLING;
				break;
			}
			
			velocity.y=0;
			break;
		case(states::JUMPING):
			//std::cout<<elapsed<<'\n';
			if(topCollision){
				state=states::FALLING;
			}
			if(bottomCollision){
				state = states::STANDING;
			}
			if(velocity.y < 4){
				velocity.y += 0.09;
			}
			break;
		default:
			state= states::FALLING; 
			break;
	}
	lastup = clock.getElapsedTime();
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
		position = sf::Vector2f(500,100);
	}
	position += velocity;
	}
}

void PlayerInput::processInput(const sf::Vector2f & velocity, const sf::Vector2f & position, sf::Vector2f & direction, const std::vector<Character> & characters){
	direction.x = 0;	//Stand still
	direction.y = 0;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		direction.x = -1;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		direction.x = 1;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
		direction.y -=1;
	}
}

/// \brief
/// Draw the Character.
/// \details
/// This function draws the Characte in the RenderWindow and sets the View to the position
/// of the Character to keep the player centered.
void PlayerGraphics::processGraphics(sf::RenderWindow & window, const sf::Vector2f & position, sf::View & view){
	sprite.setPosition(position);
	if(position.y < 300){
		view.setCenter(sf::Vector2f(position.x, position.y));
	} else {
		view.setCenter(sf::Vector2f(position.x, 300));
	}
	window.draw(sprite);
}

sf::Vector2f PlayerGraphics::getDimensions(){
	return sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
}