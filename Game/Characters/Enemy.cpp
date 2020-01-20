#include "Enemy.hpp"

void EnemyInput::processInput(const sf::Vector2f & velocity, const sf::Vector2f & position, sf::Vector2f & direction, const std::vector<Character> & characters){
	for(const Character & character : characters){
		if((character.isPlayer() && (position.x - 500 > character.getPosition().x || position.x - 500 > character.getPosition().x))){
			if(position.x > character.getPosition().x - 300){
				direction.x = -3;
			} else if(position.x < character.getPosition().x + 300){
				direction.x = 3;
			} else {
				direction.x = 0;
			}
		} else {
		}
	}
}

EnemyGraphics::EnemyGraphics(const std::string & assetName, AssetManager & assets):
	GraphicsComponent(assetName, assets)
{}

void EnemyGraphics::processGraphics(sf::RenderWindow & window, const sf::Vector2f & position, sf::View & view){
	sprite.setPosition(position);
	window.draw(sprite);
}