#ifndef __PLAYER_PLACEHOLDER
#define __PLAYER_PLACEHOLDER

#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"
#include <ctime>
#include "World.hpp"

class Player {
	private:
		sf::Sprite sprite;
        sf::View & View;
        float accel;
    	double previous, lag, current, elapsed;
        sf::Clock clock;
		float speed;
			
	public:
		Player(const std::string & assetName, AssetManager & assets, const sf::Vector2f & position, sf::View & View);
		virtual void draw(sf::RenderWindow & window);
		void move(sf::Vector2f newpos);
        		sf::FloatRect getBounds();
        void setacc(float acc);
        void update();
		bool leftcollision;
		bool rightcollision;
		bool botcol;



};

class Physics{
	public:
	void update(Player& player, World& world);


};










#endif 