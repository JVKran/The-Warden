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
		const int_fast8_t damageFactor;
	public:
		Weapon(const int_fast8_t damageFactor);
		virtual void use(Character * character, std::vector<Character> & characters) override;
};

class Consumable : public Item{
	private:
		const uint_fast8_t foodValue;
	public:
		Consumable(const uint_fast8_t foodValue);
		virtual void use(Character * character, std::vector<Character> & characters) override;
};

#endif //Items.hpp