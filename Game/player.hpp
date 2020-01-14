#ifndef __PLAYER_PLACEHOLDER
#define __PLAYER_PLACEHOLDER

#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"


class Player{
	private:
		sf::Sprite sprite;
        sf::View & View;
	public:
		Player(const std::string & assetName, AssetManager & assets, const sf::Vector2f & position, sf::View & View);
		virtual void draw(sf::RenderWindow & window);
		void move(sf::Vector2f newpos);



};











#endif 