#ifndef __SOUNDS_HPP
#define __SOUNDS_HPP

#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include <iostream>
#include "Exceptions.hpp"

class Sound {
private:
	sf::Music music;
	sf::SoundBuffer buffer;
	std::vector< sf::InputSoundFile > & soundfiles;
public:
	Sound( sf::Music music, sf::SoundBuffer buffer, std::vector< sf::InputSoundFile > & soundfiles );
	void loadMusic( std::string & filename );
	void playMusic();
	void stopMusic();
	void pauseMusic();
	void setMusicOffset( uint_fast16_t & seconds );
};

#endif //Sounds.hpp