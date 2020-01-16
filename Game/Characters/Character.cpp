#include "Character.hpp"

Character::Character(sf::Vector2f position, const std::string & assetName, AssetManager & assets,sf::RenderWindow & window):
	position(position),
	window(window),
	graphics(assetName, assets)
{}

void PlayerPhysics::processPhysics(World & world, sf::Vector2f & position, sf::Vector2f &  velocity, const sf::Vector2f & dimensions){

	if(clock.getElapsedTime().asMilliseconds()-lastup>8){
	
	
	std::vector<SelectableObject> & tiles= world.getTiles();
	sf::FloatRect tileBounds;
	bool leftCollision=0, rightCollision=0, bottomCollision=0;

	sf::FloatRect hitbox = sf::FloatRect(sf::Vector2f(position.x, position.y), sf::Vector2f(dimensions.x, dimensions.y));
	sf::FloatRect bottomHitbox = sf::FloatRect(sf::Vector2f(position.x - 2, position.y), sf::Vector2f(dimensions.x + 2, dimensions.y + 4));

	for(auto tile : tiles){
        tileBounds = tile.getBounds();
        if((hitbox.intersects(tile.getBounds()) || bottomHitbox.intersects(tile.getBounds())) && tile.isCollidable()){
        	bottomCollision += tileBounds.contains(position.x, position.y + bottomHitbox.height) || tileBounds.contains(position.x + bottomHitbox.width, position.y + bottomHitbox.height); 
        	rightCollision = tileBounds.contains(position.x + hitbox.width, position.y) || tileBounds.contains(position.x + hitbox.width, position.y + hitbox.height);
        	leftCollision = tileBounds.contains(position.x, position.y) || tileBounds.contains(position.x, position.y + hitbox.height);
       }
    }


    if(leftCollision && velocity.x < 0){
		velocity.x = 0;
	}
	
	if(rightCollision && velocity.x > 0){
		velocity.x = 0;
	}

	switch (state){
		case (states::FALLING): {
			if(bottomCollision){
				state = states::STANDING;
				velocity.y = 0;
			} else {
				velocity.y = 2;
			}
			
			break;
		}
		case (states::STANDING):
			if(velocity.y < 0){
				state = states::JUMPING;
				current = (clock.getElapsedTime().asMilliseconds());
				previous = current;
				velocity.y = -5;
				//break;
			}
			if(!bottomCollision){
				state = states::FALLING;
				break;
			}
			
			velocity.y=0;
			break;
		case(states::JUMPING):
			current = (clock.getElapsedTime().asMilliseconds());
			elapsed = current - previous;
			//std::cout<<elapsed<<'\n';
			if(elapsed > 500){
				state = states::FALLING;
				velocity.y = 0;
				break;
			}
			velocity.y = -5;
			break;
		default: 
			break;
	}

	position += velocity;
	world.getView().setCenter(sf::Vector2f(position.x, 300));
	lastup = clock.getElapsedTime().asMilliseconds();
	}
}

void PlayerInput::processInput(sf::Vector2f & velocity){
	velocity.x = 0;	//Stand still
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		velocity.x = -1;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		velocity.x = 1;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
		velocity.y -=1;
	}

	//Set velocity
	//Set animations
}

void PlayerGraphics::processGraphics(sf::RenderWindow & window, const sf::Vector2f & position){
	sprite.setPosition(position);
	window.draw(sprite);
	sf::RectangleShape doos (sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));
	doos.setPosition(position);
	window.draw(doos);
}

sf::Vector2f PlayerGraphics::getDimensions(){
	return sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
}

void Character::update(sf::RenderWindow & window, World & world){
	input.processInput(velocity);
	physics.processPhysics(world, position, velocity, graphics.getDimensions());
	graphics.processGraphics(window, position);
}

void Character::draw(){
	graphics.processGraphics(window, position);
}