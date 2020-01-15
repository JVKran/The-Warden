#include "Character.hpp"

void PlayerPhysics::processPhysics(World & world, sf::Vector2f & position,sf::Sprite &player, sf::Vector2f  velocity){
	//Refrence naar view bij world vandaan halen
	
	
	world.getView().move(velocity);
	position.x+= velocity.x;
	//std::cout<<"jowel"<<'\n';





	std::vector<ScreenObject> tiles= world.getTiles();
    sf::FloatRect hitbox = player.getGlobalBounds();
    bool leftcollision=0;
    bool rightcollision=0;
    bool bottomcol =0;
	bool landed =0;
    for(auto tile : tiles){
        sf::FloatRect tar = tile.getBounds();
        if(hitbox.intersects(tile.getBounds())){
            if((tile.getBounds().left+tile.getBounds().width<=(hitbox.left+hitbox.width))&&(tile.getBounds().top<(hitbox.top+hitbox.height-1))){
            leftcollision =1;
            //std::cout<<"jawoooooooool"; 
            }
        
        if((hitbox.left+hitbox.width<=(tile.getBounds().left+tile.getBounds().width))&&(tile.getBounds().top<(hitbox.top+hitbox.height-1))){
            rightcollision =1;
          //std::cout<<"jawoooooooool"; 
           }
        if(sf::FloatRect(hitbox.left+1,hitbox.top,hitbox.width-2,hitbox.height).intersects(tar)){
            //player.setacc(0);
            bottomcol=1;
            
          //std::cout<<"jawoooooooool"; 
           }              
        }
    }
    if(bottomcol==1){
        landed=1;   
    }
    if(leftcollision&&velocity.x<0){
		velocity.x=0;
	}
	if(rightcollision&&velocity.x>0){
		velocity.x=0;
	}
	if(!landed){
		velocity.y =1;
	}
	else if(landed){
		velocity.y=0;
	}
	player.move(velocity);

	
}

void PlayerInput::processInput(sf::Vector2f & velocity){
	velocity.x=0;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		velocity.x -=1;
	}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		velocity.x +=1;
	}
	
	//Set velocity
	//Set animations
}

void Character::update(sf::RenderWindow & window, World & world){
	input.processInput(velocity);
	physics.processPhysics(world, position,sprite, velocity);
	//sprite.setPosition(position);
}


Character::Character(sf::Vector2f pos,const std::string & assetName, AssetManager & assets,sf::RenderWindow & window):
window(window)
{
	sprite.setTexture(assets.getTexture(assetName));
	sprite.setPosition(position);
}

void Character::draw(){
	window.draw(sprite);
}