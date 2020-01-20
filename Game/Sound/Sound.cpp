#include "Sound.hpp"

Sound::Sound( sf::Music music, sf::SoundBuffer buffer, std::vector< sf::InputSoundFile > & soundfiles ):
	music( music ),
	buffer( buffer ),
	soundfiles( soundfiles )
{}

void Sound::loadMusic( std::string & filename ){
	if ( !music.openFromFile( filename ) ){
		throw unknownSoundFilename( filename );
	}
}

void Sound::playMusic(){
	std::cout<< "Playing music.\n";
	music.play();
}

void Sound::stopMusic(){
	std::cout<< "Stopped the music.\n";
	music.stop();
}
void Sound::pauseMusic(){
	std::cout<< "Paused the music.\n";
	music.pause();
}
void Sound::setMusicOffset( uint_fast16_t & seconds ){
	std::cout<< "Set offset to " << seconds << " seconds.\n";
	music.setPlayingOffset( sf::seconds( seconds ) );
}