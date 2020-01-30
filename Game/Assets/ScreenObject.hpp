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
/// It has an assetName, sprite and windowLayer to determine to which layer it is part of. i.e. when it should
/// be drawn. This is used to prevent objects being overwritten by other objects.
class ScreenObject {
	protected:
		std::string assetName;				//!< The AssetName to get corresponding texture from the AssetManager.
		sf::Sprite sprite;					//!< The Sprite this ScreenObject has to draw and manage.
		int_fast8_t windowLayer;			//!< The windowLayer this ScreenObject is part of.
	public:
		ScreenObject(const std::string & assetName, AssetManager & assets, const sf::Vector2f & position = sf::Vector2f(0,0), const float scale = 1, const float rotation = 0, const int windowLayer = 0);

		std::string getName() const;
		virtual std::string getConfiguration() const;
		sf::FloatRect getBounds() const;

		sf::Vector2f getPosition() const;
		void setPosition(const sf::Vector2f & newPosition);

		void setRotation(const float angle);
		float getRotation() const;

		void setNewScale(const float newScale);
		sf::Vector2f getScale() const;

		void setWindowLayer(const int newLayer){
			windowLayer = newLayer;
		}

		int getWindowLayer() const {
			return windowLayer;
		}

		virtual void draw(sf::RenderWindow & window) const;
};

/// \brief
/// Selectable Object
/// \details
/// This class implements a ScreenObject that can be drawn, scaled, moved, clicked and checked for collisions. 
/// It has an assetName, sprite and windowLayer to determine to which layer it is part of. Furthermore, it also has
/// several booleans that are described below.
class Tile : public ScreenObject {
	private:
		bool followMouse = false;			//!< Whether or not to follow the mouse's position.
		bool collidable = true;				//!< Whether or not Character types should collide with this Tile.
		bool hasBeenAdded = false;			//!< Whether or not this objec has been added to the tiles of the world; if it's part of the world.
		bool interactable = false;			//!< Whether or not this object can be interacted with by a Character.
		bool selected = false;				//!< Whether or not this object is currently selected (should follow the mouse cursor).
		bool passageWay = false;			//!< Whether or not this object is a passageway.
		sf::Vector2f teleportPosition;		//!< The position a Character will be teleported to when entering the passage.
	public:
		Tile(const std::string & assetName, AssetManager & assets, const sf::Vector2f & position = sf::Vector2f(0,0), sf::Vector2f teleportPosition = sf::Vector2f(0,0), const float scale = 1, const bool collidable = true, const float rotation = 0, const int windowLayer = 0, bool interactable = false);

		virtual std::string getConfiguration() const override;

		bool isPartOfWorld() const;
		void makePartOfWorld(const bool & added);

		bool isCollidable() const;
		void setCollidable(const bool newCollidable);

		bool isInteractable() const;
		void setInteractability(const bool newInteractability);

		sf::Vector2f getTeleportPosition() const;
		void changeTeleportPosition(const sf::Vector2f & newTeleportPosition);

		bool setFollowMouse(const bool follow);
		bool isFollowingMouse() const;

		bool isSelected() const;
		void changeSelected(const bool newSelected);

		void move(const sf::Vector2f & position);

		Tile& operator=(Tile lhs);
		bool operator==(Tile lhs) const;
		bool operator<(Tile lhs) const;

};

#endif //__SCREEN_OBJECT