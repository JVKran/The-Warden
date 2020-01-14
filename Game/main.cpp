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
	SpriteAnimation test2(texture1,sf::Vector2i{350,592},sf::Vector2i{7,16},3);
	
	sf::Texture texture2;
	texture2.loadFromFile("/home/hu/The-Warden/Game/Assets/Textures/PIPOYA_FREE_2D_Game_Character_Sprites/Sprite_Sheet/Enemy/Enemy003a/All/e003a_02walk.png");
	SpriteAnimation test3(texture2,sf::Vector2i{2400,2880},sf::Vector2i{5,6},2);
		
	sf::Texture texture3;
	texture3.loadFromFile("/home/hu/The-Warden/Game/Assets/Textures/PIPOYA_FREE_2D_Game_Character_Sprites/Sprite_Sheet/Enemy/Enemy001a/All/e001a_02walk.png");
	SpriteAnimation test4(texture3,sf::Vector2i{2400,2880},sf::Vector2i{5,6},2);


	/*
	int x = 2400;//350 ipv 385 vanwege lege ruimte tussen frames
	int y = 2880;
	int row = 5;//5;
	int column = 6;
	int missingRow = 2;
	
	sf::Vector2i dimensions{x,y};
	sf::Vector2i spriteRowColumn{row, column};
	
	int pixelRow = dimensions.x / spriteRowColumn.x;		// Length divided by row, these are the horizontal steps a frame 
	int pixelColumn = dimensions.y / spriteRowColumn.y;		// Height divided by column, these are the vertical steps a frame
	
	sf::IntRect rectSourceSprite(0,0,pixelRow, pixelColumn);
	sf::Sprite sprite(texture, rectSourceSprite);
	int posx = 200;
	//sprite.setScale(4,4);
	
	sprite.setPosition(posx,200);
	sf::Clock spriteClock;
	*/

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
		//window.draw(sprite);
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
		/*
		if(spriteClock.getElapsedTime().asSeconds() > 0.01f){
			if(rectSourceSprite.left == dimensions.x-pixelRow){
				rectSourceSprite.left = 0;
				rectSourceSprite.top += pixelColumn;
				
				posx-=1;
			}else if(rectSourceSprite.left == dimensions.x-pixelRow*(row-missingRow) && rectSourceSprite.top == pixelColumn*(column-1)){
				rectSourceSprite.left = 0;
				rectSourceSprite.top = 0;
				posx-=1;
			}else{ rectSourceSprite.left += pixelRow; }
			
			//std::cout<< "x = "<<rectSourceSprite.left << " y ="<<rectSourceSprite.top << "\n";
			sprite.setTextureRect(rectSourceSprite);
			//sprite.setPosition(posx,140);
			spriteClock.restart();
		}*/
	}
	return 0;
}