/// @file

#ifndef __SCREEN_OBJECT
#define __SCREEN_OBJECT

#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"
#include "FactoryFunction.hpp"

/// \brief
/// Screen Object
/// \details
/// This class implements a ScreenObject that can be drawn, scaled, moved and checked for collisions. 
/// It has an assetName, sprite and boolean to determine wether or not this object can collide with Character types.
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
		void setNewScale(const float newScale);

		sf::Vector2f getPosition() const;
		void setPosition(const sf::Vector2f & newPosition);

		virtual void draw(sf::RenderWindow & window) const;
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

		SelectableObject& operator=(SelectableObject lhs);
		bool operator==(SelectableObject lhs);
		bool operator<(SelectableObject lhs) const;

};

#endif //__SCREEN_OBJECT