#include "Enemy.hpp"

/// \brief
/// Create enemy input.
/// \details
/// This class creates the input for enemies. Based on some very simple AI; it walks towards the player if it is in sight.
/// @param position The current position of the enemy.
/// @param direction The direction the enemy should walk towards.
/// @param keys Because the InputComponent describes this function should have one.
void EnemyInput::processInput(const sf::Vector2f & position, sf::Vector2f & direction, std::vector<KeyBinding> & keys){
	int detectionRange = 80;
	for(int_fast8_t i = characters.size() - 1; i >= 0; i--){
		if(characters.at(i).isPlayer()){									//Enemy 					//Player
			if(characters.at(i).getPosition().x < position.x - detectionRange && characters.at(i).getPosition().x > position.x - 500){
				direction.x = -1;
			} else if (characters.at(i).getPosition().x > position.x + detectionRange + 30 && characters.at(i).getPosition().x - 500 < position.x){
				direction.x = 1;
			} else {
				direction.x = 0;
			}
			break;
		}
	}
}

/// \brief
/// Assignment operator.
/// \details
/// This class assigns the enemy input to another one.
/// \return A reference to itself.
EnemyInput & EnemyInput::operator=(EnemyInput lhs){
	world = lhs.world;
	characters = lhs.characters;
	return *this;
}

/// \brief
/// Process item usage.
/// \details
/// This class implements the item usage for enemies. It consists of continuously hitting...
/// @param event The sf::Event to use for detecting and handling occured events.
/// @param items The items the enemy will drop when dead.
/// @param ownCharacter This is the Character that called this function.
void EnemyInput::processItemUsage(const sf::Event & event, std::vector<std::shared_ptr<Item>> & items, Character * ownCharacter) {
	if(items.at(0)->use(ownCharacter, characters) && ownCharacter->getSelectedItem()->isWeapon()){
		ownCharacter->getGraphics()->setFightAnimation();
	}
}

/// \brief
/// Create an instance.
/// \details
/// This function creates an EnemyGraphics Component.
/// @param assetName The name of the texture to get from the AssetManager that should be used to construct te sprite.
/// @param assets The AssetManager to use to retrieve assets.
EnemyGraphics::EnemyGraphics(const std::string & assetName, AssetManager & assets):
	GraphicsComponent(assetName, assets)
{}

/// \brief
/// Process graphics.
/// \details
/// This function processes the graphics; drawing the sprite and flushing it to the renderwindow.
/// @param window The RenderWindow to draw in.
/// @param position The position of the enemy.
/// @param view The sf::View to determine the position of for making sure only the minimal is drawn.
void EnemyGraphics::processGraphics(sf::RenderWindow & window, const sf::Vector2f & position, sf::View & view){
	sprite.setPosition(position);
	window.draw(sprite);
}

/// \brief
/// Assignment operator.
/// \details
/// This class assigns the enemy input to another one.
/// \return A refrence to itself.
EnemyGraphics & EnemyGraphics::operator=(EnemyGraphics lhs){
	sprite = lhs.sprite;
	return *this;
}

/// \brief
/// Process velocity changes.
/// \details
/// This function calculates the new velocity based on the desired direction.
/// @param direction The direction the character is going to.
/// @param velocity The current velocity of the character.
void EnemyPhysics::processVelocity(sf::Vector2f & direction, sf::Vector2f & velocity){
	float maxVelocity = 0.8;
	float maxAcceleration = 0.01;
	float maxJumpAcceleration = 1;
	if(velocity.x <= maxVelocity && direction.x > 0){
    	velocity.x += direction.x * maxAcceleration;
    }

    if(velocity.x >= -maxVelocity && direction.x < 0){
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
    if(direction.y < 0 && state != states::JUMPING && state != states::FALLING){
    	velocity.y = -maxJumpAcceleration;
    }

    if(leftCollision &&direction.x<0){
		velocity.x =0;

		if(!characterCollision&&bottomCollision){
			velocity.y = -maxJumpAcceleration;
		}else if(characterCollision&&!playerCollision){
			velocity.x=1;
		}
	}
	
	if(rightCollision &&direction.x>0){
		velocity.x = 0;

		if(!characterCollision&&bottomCollision){
			velocity.y = -maxJumpAcceleration;
		}else if(characterCollision&&!playerCollision){
			velocity.x=-1;
		}
	}

	if(topCollision && !bottomCollision){
		state = states::FALLING;
		velocity.y = maxAcceleration;
	}

	if(hasResistance){
		velocity.x=velocity.x/2;
	}
}

/// \brief
/// Process velocity changes.
/// \details
/// This function calculates the new velocity based on the desired direction.
/// Almost identical to EnemyPhysics::processVelocity but jumps lower and walks slower.
/// @param direction The direction the character is going to.
/// @param velocity The current velocity of the character.
void BossPhysics::processVelocity(sf::Vector2f & direction, sf::Vector2f & velocity){
	float maxVelocity = 0.4;
	float maxAcceleration = 0.005;
	float maxJumpAcceleration = 1;
	if(velocity.x <= maxVelocity && direction.x > 0){
    	velocity.x += direction.x * maxAcceleration;
    }
    if(velocity.x >= -maxVelocity && direction.x < 0){
    	velocity.x += direction.x * maxAcceleration;
    }
    if(direction.x == 0 && velocity.x != 0){
    	if(velocity.x - 0.001 > 0){
			velocity.x = 0;
    	} else if(velocity.x + 0.001 < 0){
    		velocity.x = 0;
    	} else {
    		velocity.x = 0;
    	}
    }
    if(direction.y < 0 && state != states::JUMPING && state != states::FALLING){
    	velocity.y = -maxJumpAcceleration;
    }
    if(leftCollision && direction.x<0){
		velocity.x =0.0;
		if(!characterCollision&&bottomCollision){
			velocity.y = -maxJumpAcceleration;
		}else if(characterCollision&&!playerCollision){
			velocity.x=1;
		}
	}
	if(rightCollision &&direction.x>0){
		velocity.x = 0.0;
		//direction.x=0;
		if(!characterCollision&&bottomCollision){
			velocity.y = -maxJumpAcceleration;
		}else if(characterCollision&&!playerCollision){
			velocity.x=-1;
		}
	}
	if(topCollision && !bottomCollision){
		state = states::FALLING;
	}
	if(hasResistance){
		velocity.x=velocity.x/2;
	}
}

/// \brief
/// Create Boss input.
/// \details
/// This class creates the input for boss, it's nearly identical to the enemyinput except it is able to detect a player from further away.
/// @param position The position of the boss.
/// @param direction The direction of the boss.
/// @param keys Because the playerInput also needs one.
void BossInput::processInput(const sf::Vector2f & position, sf::Vector2f & direction, std::vector<KeyBinding> & keys){
	int detectionRange = 1;
	for(int_fast16_t i = characters.size() - 1; i >= 0; i--){
		if(characters.at(i).isPlayer()){									//Enemy 					//Player
			if(characters.at(i).getPosition().x < position.x - detectionRange && characters.at(i).getPosition().x > position.x - 2000){
				direction.x = -1;
			} else if (characters.at(i).getPosition().x > position.x + detectionRange + 30 && characters.at(i).getPosition().x - 2000 < position.x){
				direction.x = 1;
			} else {
				direction.x = 0;
			}
			break;
		}
	}
}

/// \brief
/// Process velocity changes.
/// \details
/// This function calculates the new velocity based on the desired direction.
/// Almost identical to EnemyPhysics::processVelocity but walks faster.
/// @param direction The direction the character is going to.
/// @param velocity The current velocity of the character.
void DogPhysics::processVelocity(sf::Vector2f & direction, sf::Vector2f & velocity){
	float maxVelocity = 1.1;
	float maxAcceleration = 0.03;
	float maxJumpAcceleration = 1;
	if(velocity.x <= maxVelocity && direction.x > 0){
    	velocity.x += direction.x * maxAcceleration;
    }
    if(velocity.x >= -maxVelocity && direction.x < 0){
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
    if(direction.y < 0 && state != states::JUMPING && state != states::FALLING){
    	velocity.y = -maxJumpAcceleration;
    }
    if(leftCollision &&direction.x<0){
		velocity.x =0;

		if(!characterCollision&&bottomCollision){
			velocity.y = -maxJumpAcceleration;
		}else if(characterCollision&&!playerCollision){
			velocity.x=1;
		}
	}
	if(rightCollision &&direction.x>0){
		velocity.x = 0;

		if(!characterCollision&&bottomCollision){
			velocity.y = -maxJumpAcceleration;
		}else if(characterCollision&&!playerCollision){
			velocity.x=-1;
		}
	}
	if(topCollision && !bottomCollision){
		state = states::FALLING;
		velocity.y = maxAcceleration;
	}
	if(hasResistance){
		velocity.x=velocity.x/2;
	}
}
