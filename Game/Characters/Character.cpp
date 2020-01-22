/// @file

#include "Character.hpp"

/// \brief
/// Create an instance.
/// \details
/// This creates a Character based on its parameters.
/// @param position The initial position of the Character.
/// @param input A shard pointer to an InputComponent.
/// @param physics A shaared pointer to a PhysicsComponent.
/// @param graphics A shared pointer to a GraphicsComponent.
Character::Character(sf::Vector2f position, std::shared_ptr<InputComponent> input, std::shared_ptr<PhysicsComponent> physics, std::shared_ptr<GraphicsComponent> graphics, std::shared_ptr<Item> startItem, const bool isPlayerType):
	position(position),
	isPlayerType(isPlayerType),
	input(input),
	physics(physics),
	graphics(graphics)
{
	items.push_back(startItem);
}

/// \brief
/// Update Character.
/// \details
/// This function processes the input and physics of the Character by calling
/// functions of their underlying components (InputComponent and PhysicsComponent).
/// @param window The RenderWindow to render the Character to.
/// @param world The World to perform physics calculations on.
void Character::update(sf::RenderWindow & window, World & world, std::vector<Character> & characters){
	input->processInput(position, direction);
	input->processItemUsage(items, this);
	physics->processCollisions(world, position, graphics->getDimensions(), collisionBounds);
	physics->processPhysics(velocity);
	physics->processVelocity(direction, velocity);
	if(position.y > 2000){
		health = 0;
	}
	position += velocity;
}

/// \brief
/// Is alive?
/// \return Whether or not the Character is alive.
bool Character::isAlive(){
	return health > 0;
}

/// \brief
/// Draw the Character.
/// \details
/// This function draws the Characte in the RenderWindow.
/// @param window The RenderWindow to render the Character to.
/// @param world The World to perform physics calculations on.
void Character::draw(sf::RenderWindow & window, sf::View & view){
	graphics->processGraphics(window, position, view);
}

void PhysicsComponent::processCollisions(World & world, sf::Vector2f & position, const sf::Vector2f & dimensions, CollisionBounds & collisionBounds){
	std::vector<Tile> & tiles= world.getTiles();
	std::vector<InteractableObject> & interactables = world.getInteractables();
	sf::FloatRect tileBounds;
	sf::FloatRect interactableBounds;
	leftCollision=false, rightCollision=false, bottomCollision=false, topCollision=false, hasResistance = false;

	sf::FloatRect hitbox = sf::FloatRect(sf::Vector2f(position.x, position.y), sf::Vector2f(dimensions.x, dimensions.y));
	sf::FloatRect bottomHitbox = sf::FloatRect(sf::Vector2f(position.x + 4, position.y+10 ), sf::Vector2f(dimensions.x - 8, dimensions.y -2));

	collisionBounds.leftCollisionBound = position.x - 300;
	collisionBounds.rightCollisionBound = position.x + 600;

	auto leftIterator = std::find_if(tiles.begin(), tiles.end(), [&collisionBounds](const Tile & tile)->bool{return tile.getPosition().x > collisionBounds.leftCollisionBound;});
	auto rightIterator = std::find_if(leftIterator, tiles.end(), [&collisionBounds](const Tile & tile)->bool{return tile.getPosition().x > collisionBounds.rightCollisionBound;});

	auto leftIteratorInteractable = std::find_if(interactables.begin(),     interactables.end(), [&collisionBounds](const InteractableObject & interactable)->bool{return interactable.getPosition().x > collisionBounds.leftCollisionBound;});
	auto rightIteratorInteractable = std::find_if(leftIteratorInteractable, interactables.end(), [&collisionBounds](const InteractableObject & interactable)->bool{return interactable.getPosition().x > collisionBounds.rightCollisionBound;});

	std::for_each(
		leftIterator,
		rightIterator,
		[&tileBounds, &hitbox, &bottomHitbox, this](Tile & tile){
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
	);

	std::for_each(
		leftIteratorInteractable,
		rightIteratorInteractable,
		[&interactableBounds, &hitbox, &bottomHitbox, this](InteractableObject & interactable){
			interactableBounds = interactable.getBounds();
			if(interactable.getName()=="doors_all.png"){
				if((hitbox.intersects(interactableBounds))){
					std::cout<<"We got 'em bois\n";
				}
			}
		}
	);
}

void PhysicsComponent::processVelocity(sf::Vector2f & direction, sf::Vector2f & velocity){
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
    if(direction.y < 0 && state != states::JUMPING){
    	velocity.y = -6;
    }

    if(velocity.x > -5 && direction.x < 0){
    	velocity.x += direction.x * 0.07;
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

void PhysicsComponent::processPhysics(sf::Vector2f & velocity){
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
		case (states::STANDING): {
			if(velocity.y < 0){
				state = states::JUMPING;
				break;
			}
			if(!bottomCollision){
				state = states::FALLING;
				break;
			}
			
			velocity.y=0;
			break;
		}
		case(states::JUMPING): {
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
		}
		default: {
			state= states::FALLING; 
			break;
		}
	}
}

/// \brief
/// Create an instance.
/// \details
/// This creates a GraphicsComponent based on its parameters.
/// @param assetName The name of the Texture to retrieve from the AssetManager
/// @param assets The AssetManager to retrieve textures from.
/// @param characterData The SpriteCharacter to use for getting the necessary data.
GraphicsComponent::GraphicsComponent(const std::string & assetName, AssetManager & assets){
	sprite.setTexture(assets.getTexture(assetName));
}

sf::Vector2f GraphicsComponent::getDimensions(){
	return sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
}

/// \brief
/// Is player?
/// \return Returns wether or not the Character is a player.
bool Character::isPlayer() const {
	return isPlayerType;
}

/// \brief
/// Get position of character.
/// \return Returns the position of the Character.
sf::Vector2f Character::getPosition() const {
	return position;
}

/// \brief
/// Get bounds of character.
/// \return Returns the bounds of the character.
sf::FloatRect Character::getBounds() const {
	return sf::FloatRect(position, graphics->getDimensions());
}

/// Get curent experience points.
/// \return Returns the current experience points of the Character.
int_fast16_t Character::getExperience() const{
	return experiencePoints;
}

bool Character::operator!=(const Character & lhs){
	if(lhs.position != position){
		return true;
	}
	return false;
}

bool Character::operator==(const Character & lhs){
	if(lhs.position == position){
		return true;
	}
	return false;
}

Character & Character::operator=(Character lhs){
	position = lhs.position;
	velocity = lhs.velocity;
	direction = lhs.direction;
	items = lhs.items;
	isPlayerType = lhs.isPlayerType;
	experiencePoints = lhs.experiencePoints;
	health = lhs.health;
	input = lhs.input;
	physics = lhs.physics;
	graphics = lhs.graphics;
	return *this;
}

/// \brief 
/// Set player experience points.
/// \details
/// This function adds the given experience points to the current amount of Character experience.
void Character::setExperience(const int_fast16_t & experiencePointsToAdd){
	experiencePoints += experiencePointsToAdd;
}

/// \brief
/// Get player health points.
/// \return Returns the current health points of the Character.
int_fast8_t Character::getHealth() const{
	return health;
}

/// \brief
/// Set player health points.
/// \details
/// This function adds the given health points to the current amount of Character health.
void Character::setHealth(const int_fast8_t newHealth){
	health = newHealth;
}
