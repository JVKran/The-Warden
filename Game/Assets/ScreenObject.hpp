#ifndef __SCREEN_OBJECT
#define __SCREEN_OBJECT

#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"

class ScreenObject {
	private:
		sf::Sprite sprite;
	public:
		ScreenObject(const std::string & assetName, AssetManager & assets, const sf::Vector2f & position, const float scale);

		sf::Vector2f getPosition() const;
		virtual void draw(sf::RenderWindow & window);
		sf::FloatRect getBounds();
		
};

#endif //__SCREEN_OBJECT