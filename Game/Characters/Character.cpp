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

	sf::FloatRect hitboxf = sf::FloatRect(position, dimensions);
	sf::FloatRect hitboxlarge/*(hitboxf.left-100,hitboxf.top-5,hitboxf.width+50,hitboxf.height+10)*/ (hitboxf);
	sf::FloatRect hitbox(hitboxf.left,hitboxf.top,hitboxf.width,hitboxf.height);

	for(auto tile : tiles){
        tileBounds = tile.getBounds();
        if(hitboxf.intersects(tile.getBounds())){
			//std::cout<<"coll"<<'\n';
        	if(((tileBounds.left+tileBounds.width)>=hitboxf.left)&&(tileBounds.top>hitboxf.top+hitboxf.height	)){
				std::cout<<"left"<<'\n';
				leftCollision=1;
			}
        	//rightCollision += (hitbox.left+hitbox.width<=(tile.getBounds().left+tile.getBounds().width))&&(tile.getBounds().top<(hitbox.top+hitbox.height-1));
			bottomCollision += sf::FloatRect(hitboxf.left+1,hitboxf.top,hitboxf.width-2,hitboxf.height).intersects(tileBounds);             
        }
    }

    if(leftCollision && velocity.x < 0){
		velocity.x = 0;
	}
	
	if(rightCollision && velocity.x > 0){
		velocity.x = 0;
	}

	switch (state){
		case (states::STANDING):
			//std::cout<<"STD"<<'\n';
			if(velocity.y < 0){
				state = states::JUMPING;
				current = (clock.getElapsedTime().asMilliseconds());
				previous = current;
				velocity.y = -5;
				break;
			}
			if(!bottomCollision && 1){
				state = states::FALLING;
				break;
			}
			
			velocity.y=0;
			break;
		case (states::FALLING):
			if(bottomCollision){
				state = states::STANDING;
				velocity.y = 0;
				break;
			}
			velocity.y = 5;
			
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