#include "Enemy.hpp"

void EnemyInput::processInput(const sf::Vector2f & position, sf::Vector2f & direction, std::array< KeyBinding, 3 > & keys){
	for(const Character & character : characters){
		if(character.isPlayer()){									//Enemy 					//Player
			if(character.getPosition().x < position.x - 100 && character.getPosition().x > position.x - 500){
				direction.x = -1;
			} else if (character.getPosition().x > position.x + 200 && character.getPosition().x - 500 < position.x){
				direction.x = 1;
			} else {
				direction.x = 0;
			}
		}
	}
}

EnemyGraphics::EnemyGraphics(const std::string & assetName, AssetManager & assets):
	GraphicsComponent(assetName, assets)
{}

void EnemyGraphics::processGraphics(sf::RenderWindow & window, const sf::Vector2f & position, sf::View & view){
	sprite.setPosition(position);
	window.draw(sprite);
}

void EnemyPhysics::processVelocity(sf::Vector2f & direction, sf::Vector2f & velocity){
	float maxVelocity = 0.8;
	float maxAcceleration = 0.01;
	float maxJumpAcceleration = 1;
	if(velocity.x < maxVelocity && direction.x > 0){
    	velocity.x += direction.x * maxAcceleration;
    }

    if(direction.x == 0 && velocity.x != 0){
    	if(velocity.x - 0.1 > 0){
    		velocity.x -= maxAcceleration;
    	} else if(velocity.x + 0.1 < 0){
    		velocity.x += maxAcceleration;
    	} else {
    		velocity.x = 0;
    	}
    }
    if(direction.y < 0 && state != states::JUMPING){
    	velocity.y = -maxJumpAcceleration;
    }

    if(velocity.x > -maxVelocity && direction.x < 0){
    	velocity.x += direction.x * maxAcceleration;
    }

    if(leftCollision){
		velocity.x = 0;
	}
	
	if(rightCollision){
		velocity.x = 0;
	}

	if(hasResistance){
		velocity.x=velocity.x/2;
	}
}
