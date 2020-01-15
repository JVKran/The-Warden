#include "Character.hpp"

void PlayerPhysics::processPhysics(World & world, sf::Vector2f & position,sf::Sprite &player, sf::Vector2f  &velocity){
	//bool insideOfGround =0;
	//Refrence naar view bij world vandaan halen
	
	
	//world.getView().move(velocity);
	position.x+= velocity.x;
	//std::cout<<"jowel"<<'\n';





	std::vector<ScreenObject> tiles= world.getTiles();
    sf::FloatRect hitboxf = player.getGlobalBounds();
	sf::FloatRect hitboxlarge(hitboxf.left-100,hitboxf.top-5,hitboxf.width+10,hitboxf.height+10);
	sf::FloatRect hitbox(hitboxf.left,hitboxf.top,hitboxf.width,hitboxf.height-5);
    bool leftcollision=0;
    bool rightcollision=0;
    bool bottomcol =0;
	bool landed =0;
    for(auto tile : tiles){
        sf::FloatRect tar = tile.getBounds();
        if(hitboxlarge.intersects(tile.getBounds())){
			std::cout<<tar.top<<"  top  "<<tar.top+tar.height<<"  tar bot  "<<tar.left<<"tar left"<<tar.left+tar.width<<"tar right"<<'\n'<<hitboxf.top<<"  top  "<<hitboxf.top+hitboxf.height<<"  tar bot  "<<hitboxf.left<<"tar left"<<hitboxf.left+hitboxf.width<<"tar,right"<<'\n';
            if((tile.getBounds().left+tile.getBounds().width<=(hitbox.left+hitbox.width))&&(tile.getBounds().top<(hitbox.top+hitbox.height-1))&&0){
            	leftcollision =1;
            //std::cout<<"jawoooooooool"; 
            }
        
        	if((hitbox.left+hitbox.width<=(tile.getBounds().left+tile.getBounds().width))&&(tile.getBounds().top<(hitbox.top+hitbox.height-1))){
            	rightcollision =1;
				
          	//std::cout<<"jawoooooooool"; 
           	}




        if(sf::FloatRect(hitboxf.left+1,hitboxf.top,hitboxf.width-2,hitboxf.height).intersects(tar)){
            //player.setacc(0);
            bottomcol=1;
			std::cout<<tar.height<<"  top  "<<tar.top<<"  own  "<<hitboxf.top+hitboxf.height<<"   thiers  "<<tar.top+tar.height<<'\n';
			        // if((hitbox.top+hitbox.height)>(tar.top+1)&&state == states::STANDING){
                	// player.move(sf::Vector2f(0,-0.1));
					// velocity.y=0;
					// }
					
					
					
					
            
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
	if(rightcollision&&leftcollision){
		//player.move(sf::Vector2f(0,-1));
	}
	switch (state)
	{
	case (states::STANDING):
		//std::cout<<"STD"<<'\n';
		if(velocity.y<0){
					std::cout<<"STD->JUMP"<<'\n';
			state = states::JUMPING;
			current = (clock.getElapsedTime().asMilliseconds());
			previous=current;
			velocity.y=-5;
			break;
		}
		if(!bottomcol&&0){
					std::cout<<"STD->FALL"<<'\n';
			state = states::FALLING;
			break;
		}
		
		velocity.y=0;
		break;
	case (states::FALLING):
			std::cout<<"FALL"<<'\n';
		if(bottomcol){
					std::cout<<"FALL->STD"<<'\n';
			state = states::STANDING;
			velocity.y=0;
			break;
		}
		velocity.y=5;
		
		break;
	case(states::JUMPING):
		std::cout<<"JUMP"<<'\n';
		current = (clock.getElapsedTime().asMilliseconds());
		elapsed = current - previous;
		//std::cout<<elapsed<<'\n';
		if(elapsed>500){
					std::cout<<elapsed<<'\n';
					std::cout<<"JUMP->FALL"<<'\n';
			state = states::FALLING;
			velocity.y=0;
			break;
		}
		velocity.y=-5;
		break;

	default:
		std::cout<<"OH NO"<<'\n';
		break;
	}

	player.move(velocity);
	world.getView().move(sf::Vector2f(velocity.x,0));
	

	
}

void PlayerInput::processInput(sf::Vector2f & velocity){
	velocity.x=0;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		velocity.x -=1;
	}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		velocity.x +=1;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
		velocity.y -=1;
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
 position(pos),window(window)
{
	sprite.setTexture(assets.getTexture(assetName));
	sprite.setPosition(pos);
}

void Character::draw(){
	window.draw(sprite);
}