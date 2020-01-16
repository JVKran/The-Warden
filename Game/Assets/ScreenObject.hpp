#ifndef __SCREEN_OBJECT
#define __SCREEN_OBJECT

#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"

class ScreenObject {
	protected:
		std::string assetName;
		sf::Sprite sprite;
		const bool collidable;
	public:
		ScreenObject(const std::string & assetName, AssetManager & assets, const sf::Vector2f & position, const float scale, const bool collidable = true);

		ScreenObject& operator=(ScreenObject lhs);
		bool isCollidable() const;

		std::string getConfiguration() const;

		sf::Vector2f getPosition() const;
		void setPosition(const sf::Vector2f & newPosition);

		virtual void draw(sf::RenderWindow & window);
		sf::FloatRect getBounds() const;
		
};

class SelectableObject : public ScreenObject {
	private:
		bool followMouse = false;
	public:
		bool hasBeenAdded = false;
		SelectableObject(const std::string & assetName, AssetManager & assets, const sf::Vector2f & position, const float scale, const bool collidable = true);

		bool setFollowMouse(const bool follow);
		bool isFollowingMouse() const;

		void move(const sf::Vector2f & position);
		void setNewScale(const float newScale);

		SelectableObject& operator=(SelectableObject lhs);
		bool operator==(SelectableObject lhs);
		bool operator<(SelectableObject lhs) const;

};

#endif //__SCREEN_OBJECT