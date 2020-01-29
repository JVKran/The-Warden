/// @file

#include "Character.hpp"

/// \brief
/// Create an instance.
/// \details
/// This creates a SpriteCharacter based on its parameters.
/// @param idleName
/// @param idleFile
/// @param jumpName
/// @param jumpFile
/// @param walkName
/// @param walkFile
/// @param attackName
/// @param attackFile
/// @param dieName
/// @param dieFile
SpriteCharacter::SpriteCharacter(std::string idleName,std::string idleFile,std::string jumpName, std::string jumpFile, std::string walkName, std::string walkFile,std::string attackName="", std::string attackFile="", std::string dieName="", std::string dieFile=""):
	idleName(idleName),
	idleFile(idleFile),
	jumpName(jumpName),
	jumpFile(jumpFile),
	walkName(walkName),
	walkFile(walkFile),
	attackName(attackName),
	attackFile(attackFile),
	dieName(dieName),
	dieFile(dieFile)
{}

/// \brief
/// Create an instance.
/// \details
/// This creates a Character based on its parameters.
/// @param position The initial position of the Character.
/// @param input A shared pointer to an InputComponent.
/// @param physics A shared pointer to a PhysicsComponent.
/// @param graphics A shared pointer to a GraphicsComponent.
/// @param startItems The items the character starts with.
/// @param world The world to use for determining AI paths.
/// @param isPlayerType Wether or not this character is a player.
/// @param health The health of the character.
Character::Character(sf::Vector2f position, std::shared_ptr<InputComponent> input, std::shared_ptr<PhysicsComponent> physics, std::shared_ptr<AnimatedGraphicsComponent> graphics, std::vector<std::shared_ptr<Item>> startItems, World & world, const bool isPlayerType,int_fast16_t health):
	spawnPosition(position),
	position(position),
	lootDrop(std::make_shared<LootDrop>(world)),
	isPlayerType(isPlayerType),
	health(health),
	maxHealth(health),
	healthBar(sf::Vector2f(health, 20)),
	input(input),
	physics(physics),
	graphics(graphics)

{

	items = startItems;
	healthBar.setOutlineThickness(2);
	itemSelector.setOutlineThickness(2);
	itemSelector.setSize(sf::Vector2f(25, 25));
	healthBar.setOutlineColor(sf::Color::Black);
	itemSelector.setOutlineColor(sf::Color::Black);
	itemSelector.setFillColor(sf::Color(0, 0, 0, 0));
}

void Character::die(){
	lootDrop->drop(items, experiencePoints, sf::Vector2f(position.x,position.y+graphics->getDimensions().y-10));
}
/// \brief
/// Restart the clock
/// \details
/// This function will restart the clock 
void Character::restartClock(){
	clock.restart();
	lastUpdate = 0.0;
}
/// \brief
/// Update Character.
/// \details
/// This function processes the input and physics of the Character by calling
/// functions of their underlying components (InputComponent and PhysicsComponent).
/// @param window The RenderWindow to render the Character to.
/// @param world The World to perform physics calculations on.
/// @param characters The characters to possibly hit.
/// @param keys The keys to use for input.
void Character::update(sf::RenderWindow & window, World & world, std::vector<Character> & characters, std::vector<KeyBinding> & keys){
	input->processInput(position, direction, keys);
	physics->processCollisions(items, world, position, graphics->getDimensions(), collisionBounds, characters, this);
	physics->processPhysics(velocity);
	physics->processVelocity(direction, velocity);

	if(position.y > 600 && isPlayer()){
		respawn();
		experiencePoints -= 50;
	}
	timeDifference = clock.getElapsedTime().asMilliseconds() - lastUpdate;
	if(timeDifference >= 3.0 && timeDifference <= 5.5){
		position += velocity;
		lastUpdate = clock.getElapsedTime().asMilliseconds();
	} else if(timeDifference > 6.0) {
		position += sf::Vector2f(velocity.x * ((clock.getElapsedTime().asMilliseconds() - lastUpdate) / 4), velocity.y * ((clock.getElapsedTime().asMilliseconds() - lastUpdate) / 4));
		lastUpdate = clock.getElapsedTime().asMilliseconds();

	}
}

/// \brief
/// Adds a tile
/// \details
/// This function calls the addTile function to add a new tile to the world.
/// @param event The event to use for checking clicks.
/// @param world The world to add the tile to.
/// @param window The window to use for determining the relative position of the mouse click.
/// @param view The view to use with the window to determine the abolsute position of the mouse.
void Character::addTile(const sf::Event & event, World & world, sf::RenderWindow & window, sf::View & view){
	input->addTile(event, world, window, view);
}

/// \brief
/// Adds a tile
/// \details
/// This function calls the addTile function to add a new tile to the world.
void Character::addTile(Tile & tile){
	input->addTile(tile);
}

/// \brief
/// Deletes a tile
/// \details
/// This function calls the deleteTile function to delete a 
/// tile out of the vector in the world.
/// @param event The event to use for checking clicks.
/// @param world The world to add the tile to.
/// @param window The window to use for determining the relative position of the mouse click.
/// @param view The view to use with the window to determine the abolsute position of the mouse.
void Character::deleteTile(const sf::Event & event, World & world, sf::RenderWindow & window, sf::View & view){
	input->deleteTile(event, world, window, view);
}

/// \brief
/// Handles an event
/// \details
/// Handles an event for the currently selected item.
/// @param The event for handling the selected item.
void Character::handleEvent(const sf::Event & event){
	input->handleEvent(event, selectedItem);
	input->processItemUsage(event, items, this);
}

/// \brief
/// Is alive?
/// \return Whether or not the Character is alive.
bool Character::isAlive() const {
	return health > 0;
}

/// \brief
/// Draw the Character.
/// \details
/// This function draws the Characte in the RenderWindow.
/// @param window The RenderWindow to render the Character to.
/// @param view The view to determine which parts have to be rendered and checked for collisions.
void Character::draw(sf::RenderWindow & window, sf::View & view){
	graphics->processGraphics(window, position, view);
	healthBar.setPosition(sf::Vector2f(position.x, position.y - 50));
	float redval=health*(254.0/maxHealth);
	
	healthBar.setFillColor(sf::Color(255-redval, redval, 0, 200));
	healthBar.setSize(sf::Vector2f(health, 20));
	sf::Vector2f itemPosition = sf::Vector2f(position.x, position.y - 90);
	int maxColumns = 3;
	if(isPlayer()){
		try{
			for(int_fast8_t i = items.size() - 1; i >= 0; i--){
				if(items[i]->getName() == "crate"){
					items[i]->setPosition(sf::Vector2f(itemPosition.x + 2, itemPosition.y + 2));
					items[i]->draw(window);
					items[i]->drawAmount(window);			//Amount has to be drawn after the block itself...
				} else {
					items[i]->setPosition(itemPosition);
					items[i]->draw(window);
				}
				if(i == selectedItem){
					itemSelector.setPosition(itemPosition.x, itemPosition.y);
					window.draw(itemSelector);	
				}
				itemPosition.x += 25;
				if(i % maxColumns == 0){
					itemPosition.y -= 25;
					itemPosition.x = position.x;
				}
				
			}
		} catch(std::exception & error){
			std::cout << "(!)-- " << __FILE__ <<  error.what() << std::endl;
		}
	}
	window.draw(healthBar);

	if(isPlayer()){
		//std::cout << position.x << ", " << position.y << std::endl;
	}

	sf::RectangleShape hit(graphics->getDimensions());
	hit.setPosition(position);
	hit.setFillColor(sf::Color(0,255,0,128));
	window.draw(hit);
}

/// \brief
/// Process collisions
/// \details
/// This function processes the collisions with items, tiles and characters in the world.
/// @param characterItems The items to check collisions with (after which they have to be picked up).
/// @param world The World of which the tiles have to be checked for collisions.
/// @param position 
/// @param dimensions The dimensions of the character.
/// @param collisionBounds The bounds to check for collisions in between.
/// @param characters The characters to check collisions with.
/// @param ownCharacter Pointer to the character to set a new position for.
void PhysicsComponent::processCollisions(std::vector<std::shared_ptr<Item>> & characterItems, World & world, sf::Vector2f & position, const sf::Vector2f & dimensions, CollisionBounds & collisionBounds, std::vector<Character> & characters, Character * ownCharacter){
	std::vector<Tile> & tiles= world.getTiles();
	sf::FloatRect tileBounds;
	leftCollision=false, rightCollision=false, bottomCollision=false, topCollision=false, hasResistance = false;
	characterCollision = false;
	playerCollision = false;

	sf::FloatRect hitbox = sf::FloatRect(sf::Vector2f(position.x, position.y), sf::Vector2f(dimensions.x, dimensions.y));
	sf::FloatRect bottomHitbox = sf::FloatRect(sf::Vector2f(position.x + 5 , position.y + 1.7), sf::Vector2f(dimensions.x - 10 , dimensions.y));

	collisionBounds.leftCollisionBound = position.x - 300;
	collisionBounds.rightCollisionBound = position.x + 600;

	auto leftIterator = std::find_if(tiles.begin(), tiles.end(), [&collisionBounds](const Tile & tile)->bool{return tile.getPosition().x > collisionBounds.leftCollisionBound;});
	auto rightIterator = std::find_if(leftIterator, tiles.end(), [&collisionBounds](const Tile & tile)->bool{return tile.getPosition().x > collisionBounds.rightCollisionBound;});

	std::for_each(
		
		leftIterator,
		rightIterator,
		[&tileBounds, &hitbox, &bottomHitbox, &ownCharacter, this](Tile & tile){
			tileBounds = tile.getBounds();
			if(tile.getName()=="water1"){
				if((hitbox.intersects(tileBounds) || bottomHitbox.intersects(tileBounds))){
					hasResistance += true;
	       		} 
			}
			if(tile.getName()=="OpenDoor"){
				if(hitbox.intersects(tileBounds) || bottomHitbox.intersects(tileBounds)){
					ownCharacter->setPosition(tile.getTeleportPosition());
				}
			}
	        if((hitbox.intersects(tileBounds) || bottomHitbox.intersects(tileBounds)) && tile.isCollidable()){
				bottomCollision += tileBounds.intersects(bottomHitbox); 
	        	rightCollision += tileBounds.intersects(sf::FloatRect(hitbox.left + 5,hitbox.top + 5,hitbox.width-5,hitbox.height - 5));
	        	leftCollision += tileBounds.intersects(sf::FloatRect(hitbox.left,hitbox.top + 5,hitbox.width - 5,hitbox.height - 5));
				topCollision += tileBounds.intersects(sf::FloatRect(hitbox.left + 5,hitbox.top,hitbox.width - 10,hitbox.height - 5));
	    	}
		}
	);

	for(int_fast8_t i = characters.size() - 1; i >= 0; i--){
		if(hitbox.intersects(characters.at(i).getBounds()) && characters.at(i).getPosition() != position){
			bottomCollision += characters.at(i).getBounds().intersects(bottomHitbox); 
        	rightCollision += characters.at(i).getBounds().intersects(sf::FloatRect(hitbox.left + 10,hitbox.top + 5,hitbox.width-10,hitbox.height - 7));
        	leftCollision += characters.at(i).getBounds().intersects(sf::FloatRect(hitbox.left,hitbox.top + 5,hitbox.width - 10,hitbox.height - 7));
			topCollision += characters.at(i).getBounds().intersects(sf::FloatRect(hitbox.left + 5,hitbox.top,hitbox.width - 10,hitbox.height - 5));
			characterCollision = true;
			if(characters.at(i).isPlayer()){
				playerCollision=true;
			}
		}
	}

	std::vector<std::shared_ptr<Item>> & items = world.getItems();

	for(int_fast8_t i = items.size() - 1; i >= 0; i--){
		if(hitbox.intersects(items.at(i)->getBounds()) && items.at(i)->getPosition() != position){
			if(items.at(i)->containsExperience()){
				if(ownCharacter->isPlayer()){
					std::cout << "Added " << std::to_string(items.at(i)->getExperience()) << std::endl;
					ownCharacter->addExperience(items.at(i)->getExperience());
				}
			} else {
				characterItems.push_back(items.at(i));
			}
			items.erase(std::find(items.begin(), items.end(), items.at(i)));
		}
	}
}

/// \brief
/// Process velocity changes.
/// \details
/// This function calculates the new velocity based on the desired direction.
/// @param direction The direction the character is going to.
/// @param velocity The current velocity of the character.
void PhysicsComponent::processVelocity(sf::Vector2f & direction, sf::Vector2f & velocity){
	float maxVelocity = 1;
	float maxAcceleration = 0.009;
	float maxJumpAcceleration = 1.5;
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

    if(leftCollision  && direction.x < 0){
		velocity.x = 0;
	}
	
	if(rightCollision && direction.x > 0){
		velocity.x = 0;
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
/// Process physics.
/// \details
/// This function checks for collisions, state changes and velocity changes.
/// @param velocity 
void PhysicsComponent::processPhysics(sf::Vector2f & velocity){
	float maxAcceleration = 0.005;
	float maxVelocity = 0.995;
	switch (state){
		case (states::FALLING): {
			if(bottomCollision){
				state = states::STANDING;
				velocity.y = 0;
			} else {
				if(velocity.y < maxVelocity){
					velocity.y += maxAcceleration;
				}
			}
			break;
		}
		case (states::STANDING): {
			if(velocity.y < 0&&bottomCollision){
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
			if(velocity.y < maxVelocity){
				velocity.y += maxAcceleration;
			}
			if(velocity.y > 0){
				state = states::FALLING;
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
/// Assignment operator.
/// \details
/// This function assigns one physicscomponent to the other.
/// \return Refrence to itself.
PhysicsComponent & PhysicsComponent::operator=(PhysicsComponent lhs){
	state = lhs.state;
	bottomCollision = lhs.bottomCollision;
	topCollision = lhs.topCollision;
	leftCollision = lhs.leftCollision;
	rightCollision = lhs.rightCollision;
	hasResistance = lhs.hasResistance;
	return *this;
}

/// \brief
/// Draw the Character.
/// \details
/// This function draws the Character in the RenderWindow and processes animation changes based on state changes.
/// @param window The RenderWindow to draw itself into.
/// @param position The position of the character to draw.
/// @param view The view to use for setting the position.
void AnimatedGraphicsComponent::processGraphics(sf::RenderWindow & window, const sf::Vector2f & position, sf::View & view){
	if(clock.getElapsedTime().asMilliseconds() - previousTime.asMilliseconds() > 50&&(isAttacking==false)){
		if(position != previousPosition){
			switch(state){
				case states::IDLE: {
					if(position.y < previousPosition.y){
						state = states::JUMP;
						currentAnimation =&jumpAnimation;
						if (position.x < previousPosition.x ){
							isWalkingLeft = true;
							currentAnimation->left(isWalkingLeft);
						}else{
							isWalkingLeft=false;
							currentAnimation->left(isWalkingLeft);
						}
					} else if(position.y > previousPosition.y){
						state = states::JUMP;
						currentAnimation =&jumpAnimation;
						if (position.x < previousPosition.x){
							isWalkingLeft=true;
							currentAnimation->left(isWalkingLeft);
						}else{
							isWalkingLeft=false;
							currentAnimation->left(isWalkingLeft);
						}
					}
					if (position.x < previousPosition.x){
						state = states::WALK;
						currentAnimation =&walkAnimation;
						isWalkingLeft = true;
						currentAnimation->left(isWalkingLeft);
					} else if (position.x > previousPosition.x){
						state = states::WALK;
						currentAnimation =&walkAnimation;
						isWalkingLeft = false;
						currentAnimation->left(isWalkingLeft);
					}
					break;
				}
				case states::WALK: {
					if(position.y < previousPosition.y){
						state = states::JUMP;
						currentAnimation =&jumpAnimation;
						if (position.x < previousPosition.x ){
							isWalkingLeft=true;
							currentAnimation->left(isWalkingLeft);
						}else{
							isWalkingLeft=false;
							currentAnimation->left(isWalkingLeft);
						}
					} else if (position.y > previousPosition.y){
						state = states::JUMP;
						currentAnimation =&jumpAnimation;
						if (position.x < previousPosition.x ){
							isWalkingLeft=true;
							currentAnimation->left(isWalkingLeft);

						}else{
							isWalkingLeft=false;
							currentAnimation->left(isWalkingLeft);
						}					}
					if (position.x < previousPosition.x && !isWalkingLeft){
						state = states::WALK;

						currentAnimation =&walkAnimation;
						isWalkingLeft = true;
						currentAnimation->left(isWalkingLeft);
					} else if (position.x > previousPosition.x && isWalkingLeft){
						state = states::WALK;
						currentAnimation =&walkAnimation;
						isWalkingLeft = false;
						currentAnimation->left(isWalkingLeft);
					}
					break;
				}
				case states::JUMP: {
					if(position.y == previousPosition.y){
						state = states::IDLE;
					}
					if (position.x < previousPosition.x ){
						if(!isWalkingLeft){
							isWalkingLeft = true;
							currentAnimation->left(isWalkingLeft);
						}
					}else{
						if(isWalkingLeft){
							isWalkingLeft=false;
							currentAnimation->left(isWalkingLeft);
						}
					}
					break;
				}
				default: {
					break;
				}
			}
		} else if(state != states::IDLE){
			state = states::IDLE;
			currentAnimation =&idleAnimation;
			currentAnimation->left(isWalkingLeft);
		}
		previousPosition = position;
		previousTime = clock.getElapsedTime();
	}else if (isAttacking==true)
	{
		
		if((clock.getElapsedTime().asMilliseconds()-attackTime.asMilliseconds())>500){
			state=states::IDLE;
			isAttacking=false;
			currentAnimation=&idleAnimation;
		}
	}
	
	processViewChanges(view, position);
	currentAnimation->move(sf::Vector2f(position.x,position.y));
	currentAnimation->draw(window);

}

/// \brief
/// Get dimensions of animation.
/// \return The dimensions of the currently showing animation.
sf::Vector2f AnimatedGraphicsComponent::getDimensions(){
	return currentAnimation->getDimensions();
}

/// \brief
/// Set fight animation
/// \details
/// This function sets the current animation to the fight animation.
/// @param hitTime 
void AnimatedGraphicsComponent::setFightAnimation(int_fast16_t hitTime){
	if(clock.getElapsedTime().asMilliseconds()-attackTime.asMilliseconds()>hitTime){
	isAttacking=true;
	currentAnimation=&attackAnimation;
	attackTime = clock.getElapsedTime();
	currentAnimation->left(isWalkingLeft);
	}
}

sf::FloatRect AnimatedGraphicsComponent::getGlobal() const{
	return currentAnimation->getGlobal();
}

/// \brief
/// Create an instance.
/// \details
/// This creates a GraphicsComponent based on its parameters.
/// @param assetName The name of the Texture to retrieve from the AssetManager
/// @param assets The AssetManager to retrieve textures from.
GraphicsComponent::GraphicsComponent(const std::string & assetName, AssetManager & assets){
	sprite.setTexture(assets.getTexture(assetName));
}

/// \brief
/// Get dimensions of sprite.
/// \return The dimensions of the currently showing sprite.
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

sf::FloatRect Character::getGlobal() const {
	return graphics->getGlobal();
}

/// \brief
/// Get number of selected item.
/// \return The number of the currently selected item.
int_fast16_t & Character::getSelectedItemNumber(){
	return selectedItem;
}

/// \brief
/// Set number of selected item.
/// @param number The desired new number of the currently selected item.
void Character::setSelectedItemNumber(int_fast16_t number){
		selectedItem = number;
}

/// \brief
/// Get selected item.
/// \return A shared pointer to the currently selected item.
std::shared_ptr<Item> Character::getSelectedItem(){
	return items[selectedItem];
}

/// \brief
/// Get items.
/// \return A vector with shared pointers to the items.
std::vector<std::shared_ptr<Item>> & Character::getItems(){
	return items;
}

/// Get curent experience points.
/// \return Returns the current experience points of the Character.
int_fast16_t Character::getExperience() const{
	return experiencePoints;
}

/// \brief
/// Not equal operator.
/// \return Wether or not the characters are not equal.
bool Character::operator!=(const Character & lhs){
	if(lhs.position != position){
		return true;
	}
	return false;
}

/// \brief
/// Equal operator.
/// \return Wether or not the characters are equal.
bool Character::operator==(const Character & lhs){
	if(lhs.position == position){
		return true;
	}
	return false;
}

/// \brief
/// Assignment operator.
/// \return Refrence to itself.
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
void Character::addExperience(const int_fast16_t experiencePointsToAdd){
	experiencePoints += experiencePointsToAdd;
}

/// \brief
/// Get player health points.
/// \return Returns the current health points of the Character.
int_fast16_t Character::getHealth() const{
	return health;
}

/// \brief
/// Set player health points.
/// \details
/// This function adds the given health points to the current amount of Character health.
void Character::setHealth(const int_fast16_t newHealth){
	health = newHealth;
}

/// \brief
/// Set position
/// @param newPosition The new position of the character.
void Character::setPosition(const sf::Vector2f & newPosition){
	position = newPosition;
}

/// \brief
/// Set input component
/// @param newInput The new InputComponent to use for changing direction.
void Character::setInput(std::shared_ptr<InputComponent> newInput){
	input = newInput;
}

/// \brief
/// Get GraphicsComponent
/// \return The currently active GraphicsComponent.
std::shared_ptr<AnimatedGraphicsComponent> Character::getGraphics(){
	return graphics;
}

/// \brief
/// Set spawn position
/// @param newSpawn The new desired spawn location.
void Character::setSpawn(const sf::Vector2f & newSpawn){
	spawnPosition = newSpawn;
}

/// \brief
/// Get spawn position
/// |return The current spawn position.
sf::Vector2f Character::getSpawn(){
	return spawnPosition;
}

/// \brief
/// Respawn 
/// |details
/// Set the position of the character to the spawn position.
void Character::respawn(){
	position = spawnPosition;
}