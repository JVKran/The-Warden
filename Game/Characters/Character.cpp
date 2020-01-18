#include "Character.hpp"

Character::Character(sf::Vector2f position, std::shared_ptr<InputComponent> input, std::shared_ptr<PhysicsComponent> physics, std::shared_ptr<GraphicsComponent> graphics):
	position(position),
	input(input),
	physics(physics),
	graphics(graphics)
{}

void Character::update(sf::RenderWindow & window, World & world){
	input->processInput(velocity);
	physics->processPhysics(world, position, velocity, graphics->getDimensions(), foreground);
}

void Character::draw(sf::RenderWindow & window, sf::View & view){
	graphics->processGraphics(window, position, view, foreground);
}

GraphicsComponent::GraphicsComponent(const std::string & assetName, AssetManager & assets, spriteCharacter & characterData):
	characterData(characterData)
{
	sprite.setTexture(assets.getTexture(assetName));
}
