#ifndef __SCREEN_OBJECT
#define __SCREEN_OBJECT

#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"

class ScreenObject {
	protected:
		std::string assetName;
		sf::Sprite sprite;
	public:
		ScreenObject(const std::string & assetName, AssetManager & assets, const sf::Vector2f & position, const float scale);

		ScreenObject& operator=(ScreenObject lhs);

		std::string getConfiguration() const;

		sf::Vector2f getPosition() const;
		virtual void draw(sf::RenderWindow & window);
		sf::FloatRect getBounds() const;
		
};

class SelectableObject : public ScreenObject {
	private:
		bool followMouse = false;
	public:
		SelectableObject(const std::string & assetName, AssetManager & assets, const sf::Vector2f & position, const float scale);

		bool setFollowMouse(const bool follow);

		void move(const sf::Vector2i & position);

		SelectableObject& operator=(SelectableObject lhs);
		bool operator==(SelectableObject lhs);
		bool operator<(SelectableObject lhs) const;

};

#endif //__SCREEN_OBJECT