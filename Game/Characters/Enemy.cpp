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
	if(velocity.x < 4 && direction.x > 0){
    	velocity.x += direction.x * 0.05;
    }

    if(direction.x == 0 && velocity.x != 0){
    	if(velocity.x - 0.1 > 0){
    		velocity.x -= 0.05;
    	} else if(velocity.x + 0.1 < 0){
    		velocity.x += 0.05;
    	} else {
    		velocity.x = 0;
    	}
    }
    if(direction.y < 0 && state != states::JUMPING){
    	velocity.y = -5;
    }

    if(velocity.x > -4 && direction.x < 0){
    	velocity.x += direction.x * 0.05;
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
