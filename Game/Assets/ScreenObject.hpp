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
		std::string assetName;				//!< The AssetName to get corresponding texture from the AssetManager.
		sf::Sprite sprite;					//!< The Sprite this ScreenObject has to draw and manage.
		bool collidable;					//!< Wether or not Character types should collide with this ScreenObject.
	public:
		ScreenObject(const std::string & assetName, AssetManager & assets, const sf::Vector2f & position, const float scale, const bool collidable = true, const float rotation = 0);

		bool isCollidable() const;
		void setCollidable(const bool newCollidable);

		std::string getConfiguration() const;

		sf::FloatRect getBounds() const;
		sf::Vector2f getPosition() const;
		void setPosition(const sf::Vector2f & newPosition);
		void setRotation(const float angle);
		float getRotation() const;

		void setNewScale(const float newScale);
		sf::Vector2f getScale() const;

		virtual void draw(sf::RenderWindow & window) const;
};

/// \brief
/// Selectable Object
/// \details
/// This class implements a ScreenObject that can be drawn, scaled, moved, clicked and checked for collisions. 
/// It has an assetName, sprite and boolean to determine wether or not this object can collide with Character types.
class SelectableObject : public ScreenObject {
	private:
		bool followMouse = false;			//!< Wether or not to follow the mouse's position.
	public:
		bool hasBeenAdded = false;			//!< Wether or not this objec has been added to the tiles of the world; if it's part of the world.
		SelectableObject(const std::string & assetName, AssetManager & assets, const sf::Vector2f & position, const float scale, const bool collidable = true, const float rotation = 0);

		bool setFollowMouse(const bool follow);
		bool isFollowingMouse() const;
		std::string getName() const;

		void move(const sf::Vector2f & position);

		SelectableObject& operator=(SelectableObject lhs);
		bool operator==(SelectableObject lhs) const;
		bool operator<(SelectableObject lhs) const;

};

#endif //__SCREEN_OBJECT