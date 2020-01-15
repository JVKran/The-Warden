#include "player.hpp"

Player::Player(const std::string & assetName, AssetManager & assets, const sf::Vector2f & position, sf::View & View):
 View(View)
{
	sprite.setTexture(assets.getTexture(assetName));
	sprite.setPosition(position);
    
}

void Player::draw(sf::RenderWindow & window){
    window.draw(sprite);
}

sf::FloatRect Player::getBounds(){
	return(sprite.getGlobalBounds());
}
void Player::setacc(float acc){
    accel= acc;
}

void Player::update(){
    current = (clock.getElapsedTime().asMilliseconds());
	elapsed = current - previous;
	//previous = current;
    if(botcol==1){
        accel =0;
        speed =0;
    }
    if(elapsed>15){
        speed+=accel*0.015;
        //std::cout<<"jawoooooooel";
        previous = current;
        
      move(sf::Vector2f(0,speed));
    }
}

void Player::move(sf::Vector2f newpos){
    sprite.move(newpos);
    View.move(sf::Vector2f(newpos.x, 0));
}

void Physics::update(Player& player, World& world){
    std::vector<ScreenObject> tiles= world.getTiles();
    sf::FloatRect hitbox = player.getBounds();
    player.leftcollision=0;
    player.rightcollision=0;
    bool bottomcol =0;
    for(auto tile : tiles){
        sf::FloatRect tar = tile.getBounds();
        if(hitbox.intersects(tile.getBounds())){
            if((tile.getBounds().left+tile.getBounds().width<=(hitbox.left+hitbox.width))&&(tile.getBounds().top<(hitbox.top+hitbox.height-1))){
            player.leftcollision =1;
            //std::cout<<"jawoooooooool"; 
            }
        
        if((hitbox.left+hitbox.width<=(tile.getBounds().left+tile.getBounds().width))&&(tile.getBounds().top<(hitbox.top+hitbox.height-1))){
            player.rightcollision =1;
          //std::cout<<"jawoooooooool"; 
           }
        if(sf::FloatRect(hitbox.left+1,hitbox.top,hitbox.width-2,hitbox.height).intersects(tar)){
            //player.setacc(0);
            bottomcol=1;
            player.botcol=1;
          //std::cout<<"jawoooooooool"; 
           }              
        }
    }
    if(bottomcol==0){
        player.landed=0;
        player.botcol=0;
        player.setacc(9);   
    }
    player.update();
}