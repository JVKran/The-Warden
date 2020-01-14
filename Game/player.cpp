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

void Player::move(sf::Vector2f newpos){
    sprite.move(newpos);
    View.move(sf::Vector2f(newpos.x, 0));
}