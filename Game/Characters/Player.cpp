/// @file
#include <iostream>
#include "Player.hpp"

/// \brief
/// Draw the Character.
/// \details
/// This function draws the Characte in the RenderWindow and sets the View to the position
/// of the Character to keep the player centered.
void PlayerGraphics::processGraphics(sf::RenderWindow & window, const sf::Vector2f & position, sf::View & view){
	sprite.setPosition(position);
	if(position.y < 300){
		view.setCenter(sf::Vector2f(position.x, position.y));
	} else {
		view.setCenter(sf::Vector2f(position.x, 300));
	}
	window.draw(sprite);
}

sf::Vector2f PlayerGraphics::getDimensions(){
	return sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
}

AnimatedPlayerGraphics::AnimatedPlayerGraphics(const std::string & assetName, AssetManager & assets, SpriteCharacter & characterData):
	
	AnimatedGraphicsComponent(assetName, assets /*characterData*/),
	idleAnimation(assets,spriteIdle,characterData.idleName,characterData.idleFile),
	jumpAnimation(assets,spriteJump,characterData.jumpName,characterData.jumpFile),
	walkAnimation(assets,spriteWalk,characterData.walkName,characterData.walkFile),
	attackAnimation(assets,spriteAttack,characterData.attackName,characterData.attackFile),
	currentAnimation(&idleAnimation)

	//Animation(sprite, assets.getTexture(assetName), characterData.spriteCharacterData[0] /* sf::Vector2i{2400,1440}*/, /*sf::Vector2i{5,3}*/characterData.spriteCharacterData[1],  characterData.spriteCharacterData[2] , characterData.spriteCharacterData[3])
{}

/// \brief
/// Draw the Character.
/// \details
/// This function draws the Characte in the RenderWindow and sets the View to the position
/// of the Character to keep the player centered.
void AnimatedPlayerGraphics::processGraphics(sf::RenderWindow & window, const sf::Vector2f & position, sf::View & view){

	if(clock.getElapsedTime().asMilliseconds() - previousTime.asMilliseconds() > 50){
		if(position != previousPosition){
			switch(state){
				case states::IDLE: {
					if(position.y < previousPosition.y){
						state = states::JUMP;
						currentAnimation =&jumpAnimation;
						if (position.x < previousPosition.x ){
							isWalkingLeft = true;
							currentAnimation->left(isWalkingLeft);
						}else{
							isWalkingLeft=false;
							currentAnimation->left(isWalkingLeft);
						}
					} else if(position.y > previousPosition.y){
						state = states::JUMP;
						currentAnimation =&jumpAnimation;
						if (position.x < previousPosition.x){
							isWalkingLeft=true;
							currentAnimation->left(isWalkingLeft);
						}else{
							isWalkingLeft=false;
							currentAnimation->left(isWalkingLeft);
						}
					}
					if (position.x < previousPosition.x){
						state = states::WALK;
						currentAnimation =&walkAnimation;
						isWalkingLeft = true;
						currentAnimation->left(isWalkingLeft);
					} else if (position.x > previousPosition.x){
						state = states::WALK;
						currentAnimation =&walkAnimation;
						isWalkingLeft = false;
						currentAnimation->left(isWalkingLeft);
					}
					break;
				}
				case states::WALK: {
					if(position.y < previousPosition.y){
						state = states::JUMP;
						currentAnimation =&jumpAnimation;
						if (position.x < previousPosition.x ){
							isWalkingLeft=true;
							currentAnimation->left(isWalkingLeft);
						}else{
							isWalkingLeft=false;
							currentAnimation->left(isWalkingLeft);
						}
					} else if (position.y > previousPosition.y){
						state = states::JUMP;
						currentAnimation =&jumpAnimation;
						if (position.x < previousPosition.x ){
							isWalkingLeft=true;
							currentAnimation->left(isWalkingLeft);

						}else{
							isWalkingLeft=false;
							currentAnimation->left(isWalkingLeft);
						}					}
					if (position.x < previousPosition.x && !isWalkingLeft){
						state = states::WALK;

						currentAnimation =&walkAnimation;
						isWalkingLeft = true;
						currentAnimation->left(isWalkingLeft);
					} else if (position.x > previousPosition.x && isWalkingLeft){
						state = states::WALK;
						currentAnimation =&walkAnimation;
						isWalkingLeft = false;
						currentAnimation->left(isWalkingLeft);
					}
					break;
				}
				case states::JUMP: {
					if(position.y == previousPosition.y){
						state = states::IDLE;
					}
					if (position.x < previousPosition.x ){
						if(!isWalkingLeft){
							isWalkingLeft = true;
							currentAnimation->left(isWalkingLeft);
						}
					}else{
						if(isWalkingLeft){
							isWalkingLeft=false;
							currentAnimation->left(isWalkingLeft);
						}
					}
					break;
				}
				default: {
					break;
				}
			}
		} else if(state != states::IDLE){
			state = states::IDLE;
			currentAnimation =&idleAnimation;
			currentAnimation->left(isWalkingLeft);
		}
		previousPosition = position;
		previousTime = clock.getElapsedTime();
	}
	currentAnimation->move(sf::Vector2f(position.x,position.y));
	if(position.y < 300){
		view.setCenter(sf::Vector2f(position.x, position.y));
	} else {
		view.setCenter(sf::Vector2f(position.x, 300));
	}
	currentAnimation->draw(window);

}

sf::Vector2f AnimatedPlayerGraphics::getDimensions(){
	//return sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
	return currentAnimation->getDimensions();
}

PlayerGraphics::PlayerGraphics(const std::string & assetName, AssetManager & assets):
	GraphicsComponent(assetName, assets)
{}

void PlayerInput::processInput(const sf::Vector2f & position, sf::Vector2f & direction, std::array< KeyBinding, 3 > & keys){
	direction.x = 0;	//Stand still
	direction.y = 0;
	if(sf::Keyboard::isKeyPressed(keys[0].getKey())){
		direction.x = -1;
	}
	if(sf::Keyboard::isKeyPressed(keys[1].getKey())){
		direction.x = 1;
	}
	if(sf::Keyboard::isKeyPressed(keys[2].getKey())){
		direction.y = -1;
	}
}



void PlayerInput::processItemUsage(std::vector<std::shared_ptr<Item>> & items, Character * ownCharacter){
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		items.at(ownCharacter->getSelectedItem())->use(ownCharacter, characters);
	}
}

void PlayerInput::handleEvent(const sf::Event & event, int_fast16_t & selectedItem){
	if(event.type == sf::Event::MouseWheelMoved){	
		selectedItem += event.mouseWheel.delta;
	}
}
