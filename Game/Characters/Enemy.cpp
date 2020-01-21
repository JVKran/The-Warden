#include "Enemy.hpp"

void EnemyInput::processInput(const sf::Vector2f & velocity, const sf::Vector2f & position, sf::Vector2f & direction, const std::vector<Character> & characters){
	for(const Character & character : characters){
		if((character.isPlayer() && (position.x  > character.getPosition().x - 500 || position.x < character.getPosition().x + 500))){
			if(position.x > character.getPosition().x - 300){
				direction.x = -1;
			} else if(position.x < character.getPosition().x + 300){
				direction.x = 1;
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