#ifndef __ITEMS_HPP
#define __ITEMS_HPP

#include <vector>
#include <cstdint>
#include "Character.hpp"

class Character; 

class Item{
	public:
		virtual void use(Character * character, std::vector<Character> & characters) = 0;
};

class Weapon : public Item{
	private:	
		const int damageFactor;
	public:
		Weapon(const int damageFactor);
		virtual void use(Character * character, std::vector<Character> & characters) override;
};

class Consumable : public Item{
	private:
		const int foodValue;
	public:
		Consumable(const int foodValue);
		virtual void use(Character * character, std::vector<Character> & characters) override;
};

#endif //Items.hpp