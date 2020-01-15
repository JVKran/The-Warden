#ifndef __WEAPON_HPP
#define __WEAPON_HPP

#include < SFML/Graphics.hpp >

class Weapon { 
private:
	float & damage;
	float & range;
	sf::Sprite & sprite;
public:
	Weapon( float & damage = 20.0, float & range = 50.0, sf::Sprite & sprite );
};

#endif // Weapon.hpp