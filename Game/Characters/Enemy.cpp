#include "Enemy.hpp"

void EnemyInput::processInput(sf::Vector2f & velocity, const sf::Vector2f & position, const std::vector<Character> & characters){
	for(const Character & character : characters){
		if(character.isPlayer() && position.x + 1000 < character.getPosition().x && position.x - 1000 > character.getPosition().x){
			if(character.getPosition().x > position.x){
				velocity.x += 5;
			} else {
				velocity.x -= 5;
			}
		}
	}
}