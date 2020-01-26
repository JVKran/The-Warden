#include "Audio.hpp"

Sound::Sound(const std::string & filename):
	filename(filename)
{
	buffer.loadFromFile(filename);
	sound.setBuffer(buffer);
}

void Sound::playSound(){
	sound.play();
}

Music::Music(const std::string & filename):
	filename(filename)
{
	music.openFromFile(filename);
}

void Music::playMusic(){
	music.play();
}

void Music::pauseMusic(){
	music.pause();
}

void Music::stopMusic(){
	music.stop();
}


void Music::setMusicVolume(const float & newVolume){
	music.setVolume(newVolume);
}