#ifndef __SCREEN_OBJECT
#define __SCREEN_OBJECT

#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"

class ScreenObject {
	private:
		sf::Sprite sprite;
	public:
		ScreenObject(const std::string & assetName, AssetManager & assets);
		virtual void draw(sf::RenderWindow & window);
		
};

#endif //__SCREEN_OBJECT