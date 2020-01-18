#include "Character.hpp"

Character::Character(sf::Vector2f position, sf::RenderWindow & window, std::shared_ptr<InputComponent> input, std::shared_ptr<PhysicsComponent> physics, std::shared_ptr<GraphicsComponent> graphics):
	position(position),
	window(window),
	input(input),
	physics(physics),
	graphics(graphics)
{}

void Character::update(sf::RenderWindow & window, World & world){
	input->processInput(velocity);
	physics->processPhysics(world, position, velocity, graphics->getDimensions(), window, foreground);
	graphics->processGraphics(window, position, foreground);
}

void Character::draw(){
	graphics->processGraphics(window, position,foreground);
}

GraphicsComponent::GraphicsComponent(const std::string & assetName, AssetManager & assets, spriteCharacter & characterData):
	characterData(characterData)
{
	sprite.setTexture(assets.getTexture(assetName));
}
