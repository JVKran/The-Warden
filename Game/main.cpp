#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"
#include "World.hpp"

int main(){
	AssetManager assets;
	assets.loadObjects("objects.txt");

	World world(assets);
	world.loadWorld("world.txt");

	sf::RenderWindow window{ sf::VideoMode{ 1000, 580 }, "The Warden" };
	sf::Texture texture;
	texture.loadFromFile("/home/hu/The-Warden/Game/Assets/Textures/PIPOYA_FREE_2D_Game_Character_Sprites/Sprite_Sheet/Enemy/Enemy001a/All/e001a_02walk.png");
	sf::IntRect rectSourceSprite(0,0,480,480);
	sf::Sprite sprite(texture, rectSourceSprite);
	int posx = 200;
	sprite.setPosition(posx,140);
	sf::Clock spriteClock;

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
		window.draw(sprite);

		window.display();
		sf::sleep( sf::milliseconds( 10 ));

		sf::Event event;		
	    while( window.pollEvent(event) ){
			if( event.type == sf::Event::Closed ){
				window.close();
			}
		}
		// render();
		if(spriteClock.getElapsedTime().asSeconds() > 0.01f){
			if(rectSourceSprite.left == 1920){
				rectSourceSprite.left = 0;
				rectSourceSprite.top += 480;
				
				posx-=1;
			}else if(rectSourceSprite.left == 960 && rectSourceSprite.top == 2400){
				rectSourceSprite.left = 0;
				rectSourceSprite.top = 0;
				posx-=1;
			}else{ rectSourceSprite.left += 480; }
			
			sprite.setPosition(posx,140);
			sprite.setTextureRect(rectSourceSprite);
			spriteClock.restart();
		}
	}
	return 0;
}