/// @file

#include "Character.hpp"

/// \brief
/// Create an instance.
/// \details
/// This creates a SpriteCharacter based on its parameters.
/// @param spriteCharacterData The vector with Vector2i's used for positioning the spritesheet.
/// @param spriteCharacterAction No idea.
/// @param spriteCharacterNames All available actions to perform.
SpriteCharacter::SpriteCharacter(std::vector<sf::Vector2i> spriteCharacterData, std::vector<sf::Vector2i> spriteCharacterAction, std::vector<std::string> spriteCharacterNames):
	spriteCharacterData(spriteCharacterData),
	spriteCharacterAction(spriteCharacterAction),
	spriteCharacterNames(spriteCharacterNames)
{}

/// \brief
/// Create an instance.
/// \details
/// This creates a Character based on its parameters.
/// @param position The initial position of the Character.
/// @param input A shard pointer to an InputComponent.
/// @param physics A shaared pointer to a PhysicsComponent.
/// @param graphics A shared pointer to a GraphicsComponent.
Character::Character(sf::Vector2f position, std::shared_ptr<InputComponent> input, std::shared_ptr<PhysicsComponent> physics, std::shared_ptr<GraphicsComponent> graphics):
	position(position),
	input(input),
	physics(physics),
	graphics(graphics)
{}

/// \brief
/// Update Character.
/// \details
/// This function processes the input and physics of the Character by calling
/// functions of their underlying components (InputComponent and PhysicsComponent).
/// @param window The RenderWindow to render the Character to.
/// @param world The World to perform physics calculations on.
void Character::update(sf::RenderWindow & window, World & world){
	input->processInput(velocity);
	physics->processPhysics(world, position, velocity, graphics->getDimensions());
}

/// \brief
/// Draw the Character.
/// \details
/// This function draws the Characte in the RenderWindow.
/// @param window The RenderWindow to render the Character to.
/// @param world The World to perform physics calculations on.
void Character::draw(sf::RenderWindow & window, sf::View & view){
	graphics->processGraphics(window, position, view);
}

/// \brief
/// Create an instance.
/// \details
/// This creates a GraphicsComponent based on its parameters.
/// @param assetName The name of the Texture to retrieve from the AssetManager
/// @param assets The AssetManager to retrieve textures from.
/// @param characterData The SpriteCharacter to use for getting the necessary data.
GraphicsComponent::GraphicsComponent(const std::string & assetName, AssetManager & assets, SpriteCharacter & characterData):
	characterData(characterData)
{
	sprite.setTexture(assets.getTexture(assetName));
}
