#ifndef __ATTACK_HPP
#define __ATTACK_HPP

#include < vector >

class Attack {
private:
	// std::vector< Animation > animations;
	// std::vector< Character > characters;
public:
	Attack( Character & character );
	update( std::vector< Character > & characters );
};

#endif // Attacks.hpp