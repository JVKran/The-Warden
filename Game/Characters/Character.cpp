#include "Character.hpp"

Character::Character(sf::Vector2f position, const std::string & assetName, AssetManager & assets,sf::RenderWindow & window, std::vector<sf::Vector2i> spriteCharacterData, 
			 std::vector<sf::Vector2i> spriteCharacterAction, std::vector<std::string> spriteCharacterNames):
	position(position),
	window(window),
	graphics(assetName, assets, spriteCharacterData, spriteCharacterAction,spriteCharacterNames)
{}

void PlayerPhysics::processPhysics(World & world, sf::Vector2f & position, sf::Vector2f velocity, const sf::Vector2f & dimensions){
	std::vector<SelectableObject> & tiles= world.getTiles();
	sf::FloatRect tileBounds;
	bool leftCollision, rightCollision, bottomCollision;

	sf::FloatRect hitboxf = sf::FloatRect(position, dimensions);
	sf::FloatRect hitboxlarge(hitboxf.left-100,hitboxf.top-5,hitboxf.width+10,hitboxf.height+10);
	sf::FloatRect hitbox(hitboxf.left,hitboxf.top,hitboxf.width,hitboxf.height-5);

	for(auto tile : tiles){
        tileBounds = tile.getBounds();
        if(hitboxlarge.intersects(tile.getBounds())){
        	leftCollision = ((tile.getBounds().left + tile.getBounds().width <= (hitbox.left+hitbox.width)) && (tile.getBounds().top < (hitbox.top+hitbox.height - 1)) && 0);
        	rightCollision = (hitbox.left+hitbox.width<=(tile.getBounds().left+tile.getBounds().width))&&(tile.getBounds().top<(hitbox.top+hitbox.height-1));
			bottomCollision = sf::FloatRect(hitboxf.left+1,hitboxf.top,hitboxf.width-2,hitboxf.height).intersects(tileBounds);             
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
			if(!bottomCollision && 0){
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

void PlayerGraphics::processGraphics(sf::RenderWindow & window, const sf::Vector2f & position, std::string name){
	sprite.setPosition(position);
	Animation.changeStartEndFrame(animation[name][0], animation[name][1]);
	Animation.draw(window);
}

sf::Vector2f PlayerGraphics::getDimensions(){
	return sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
}

void Character::update(sf::RenderWindow & window, World & world){
	input.processInput(velocity);
	physics.processPhysics(world, position, velocity, graphics.getDimensions());
	graphics.processGraphics(window, position, action);
}

void Character::draw(){
	graphics.processGraphics(window, position, action);
}