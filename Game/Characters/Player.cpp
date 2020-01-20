/// @file

#include "Player.hpp"

PlayerGraphics::PlayerGraphics(const std::string & assetName, AssetManager & assets):
	GraphicsComponent(assetName, assets)
{}


void PlayerPhysics::processPhysics(World & world, sf::Vector2f & position, sf::Vector2f & velocity, sf::Vector2f & direction, const sf::Vector2f & dimensions){

	if(clock.getElapsedTime().asMilliseconds() - lastup.asMilliseconds() > 2){
	
	
	std::vector<Tile> & tiles= world.getTiles();
	sf::FloatRect tileBounds;
	leftCollision=false, rightCollision=false, bottomCollision=false, topCollision=false, hasResistance = false;

	sf::FloatRect hitbox = sf::FloatRect(sf::Vector2f(position.x, position.y), sf::Vector2f(dimensions.x, dimensions.y));
	sf::FloatRect bottomHitbox = sf::FloatRect(sf::Vector2f(position.x + 4, position.y+10 ), sf::Vector2f(dimensions.x - 8, dimensions.y -2));
	for(const auto & tile : tiles){

        tileBounds = tile.getBounds();
		if(tile.getName()=="water1"){
			if((hitbox.intersects(tileBounds) /*|| bottomHitbox.intersects(tileBounds)*/)){
				hasResistance += true;
       		} 
		}
        if((hitbox.intersects(tileBounds) || bottomHitbox.intersects(tileBounds)) && tile.isCollidable()){
        	bottomCollision += tileBounds.intersects(bottomHitbox); 
        	rightCollision += tileBounds.intersects(sf::FloatRect(hitbox.left+10,hitbox.top,hitbox.width-10,hitbox.height));
        	leftCollision += tileBounds.intersects(sf::FloatRect(hitbox.left,hitbox.top,hitbox.width-10,hitbox.height));
			topCollision += tileBounds.intersects(sf::FloatRect(hitbox.left+5,hitbox.top,hitbox.width-10,hitbox.height-5));
			
       }
    }

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

    if(velocity.x < 5 && direction.x > 0){
    	velocity.x += direction.x * 0.07;
    }
    if(direction.x == 0 && velocity.x != 0){
    	if(velocity.x - 0.1 > 0){
    		velocity.x -= 0.07;
    	} else if(velocity.x + 0.1 < 0){
    		velocity.x += 0.07;
    	} else {
    		velocity.x = 0;
    	}
    }
    if(velocity.x > -5 && direction.x < 0){
    	velocity.x += direction.x * 0.07;
    }
    //velocity.x = direction.x;


    if(leftCollision && direction.x < 0){
		velocity.x = 0;
	}
	
	if(rightCollision && direction.x > 0){
		velocity.x = 0;
	}
	if(hasResistance){
		velocity.x=velocity.x/2;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::T)){
		position = sf::Vector2f(-100,100);
	}
	position += velocity;
	}
}

void PlayerInput::processInput(sf::Vector2f & velocity, const sf::Vector2f & position, sf::Vector2f & direction, const std::vector<Character> & characters){
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