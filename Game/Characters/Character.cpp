#include "Character.hpp"

Character::Character(sf::Vector2f position, std::shared_ptr<InputComponent> input, std::shared_ptr<PhysicsComponent> physics, std::shared_ptr<GraphicsComponent> graphics):
	position(position),
	input(input),
	physics(physics),
	graphics(graphics)
{}

void Character::update(sf::RenderWindow & window, World & world){
	input->processInput(direction);
	physics->processPhysics(world, position, velocity, direction, graphics->getDimensions());
}

void Character::draw(sf::RenderWindow & window, sf::View & view){
	graphics->processGraphics(window, position, view);
	// sf::RectangleShape hit(graphics->getDimensions());
	// hit.setPosition(position);
	// hit.setFillColor(sf::Color(0,255,0,128));
	// window.draw(hit);
	// debug draw hitbox
	//window.display();
}

GraphicsComponent::GraphicsComponent(const std::string & assetName, AssetManager & assets, spriteCharacter & characterData):
	characterData(characterData)
{
	sprite.setTexture(assets.getTexture(assetName));
}
