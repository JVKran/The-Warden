#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"
#include "World.hpp"
#include "SpriteAnimation.hpp"

int main(){
	AssetManager assets;
	assets.loadObjects("objects.txt");

	World world(assets);
	world.loadWorld("world.txt");

	sf::RenderWindow window{ sf::VideoMode{ 1000, 580 }, "The Warden" };
	
	sf::Texture texture;
	texture.loadFromFile("/home/hu/The-Warden/Game/Assets/Textures/PIPOYA_FREE_2D_Game_Character_Sprites/Sprite_Sheet/Enemy/Enemy002a/All/e002a_02walk.png");
	SpriteAnimation test1(texture,sf::Vector2i{2400,2880},sf::Vector2i{5,6},2);
	
	sf::Texture texture1;
	texture1.loadFromFile("/home/hu/The-Warden/Game/Assets/Textures/adventurer-v1.5-Sheet.png");
	SpriteAnimation test2(texture1,sf::Vector2i{350,592},sf::Vector2i{7,16},3, sf::Vector2f{10,10});
	
	sf::Texture texture2;
	texture2.loadFromFile("/home/hu/The-Warden/Game/Assets/Textures/PIPOYA_FREE_2D_Game_Character_Sprites/Sprite_Sheet/Witch/Character_color1/All/c00a_12skill.png");
	SpriteAnimation test3(texture2,sf::Vector2i{2400,1920},sf::Vector2i{5,4},2);
		
	sf::Texture texture3;
	texture3.loadFromFile("/home/hu/The-Warden/Game/Assets/Textures/PIPOYA_FREE_2D_Game_Character_Sprites/Sprite_Sheet/Enemy/Enemy001a/All/e001a_02walk.png");
	SpriteAnimation test4(texture3,sf::Vector2i{2400,2880},sf::Vector2i{5,6},2);

	sf::Clock clock;
	uint_fast8_t msPerUpdate = 16;
	double previous, lag, current, elapsed;
	
	while (window.isOpen()){
		current = (clock.getElapsedTime().asMilliseconds());
		elapsed = current - previous;
		previous = current;
		lag += elapsed;

		// processInput();

		while (lag >= msPerUpdate){
			lag -= msPerUpdate;
		}

		window.clear();
		world.draw(window);
		test2.draw(window);
		test3.draw(window);
		test1.draw(window);
		test4.draw(window);


		window.display();
		sf::sleep( sf::milliseconds( 10 ));

		sf::Event event;		
	    while( window.pollEvent(event) ){
			if( event.type == sf::Event::Closed ){
				window.close();
			}
		}
		
		
		// render();
	}
	return 0;
}