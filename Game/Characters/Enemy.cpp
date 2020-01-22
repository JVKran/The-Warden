#include "Enemy.hpp"

void EnemyInput::processInput(const sf::Vector2f & position, sf::Vector2f & direction){
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
	if(velocity.x < 3 && direction.x > 0){
    	velocity.x += direction.x * 0.04;
    }

    if(direction.x == 0 && velocity.x != 0){
    	if(velocity.x - 0.1 > 0){
    		velocity.x -= 0.04;
    	} else if(velocity.x + 0.1 < 0){
    		velocity.x += 0.04;
    	} else {
    		velocity.x = 0;
    	}
    }
    if(velocity.x > -3 && direction.x < 0){
    	velocity.x += direction.x * 0.04;
    }

    if(leftCollision && direction.x < 0){
		velocity.x = 0;
	}
	
	if(rightCollision && direction.x > 0){
		velocity.x = 0;
	}

	if(hasResistance){
		velocity.x=velocity.x/2;
	}
}