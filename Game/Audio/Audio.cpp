/// @file

#include "Audio.hpp"

/// \brief
/// Create an instance
/// \details
/// This loads the sound in the file into the buffer.
Sound::Sound(const std::string & filename):
	filename(filename)
{
	if(!buffer.loadFromFile(filename)){
		std::cerr << "(!)-- Error loading sound in file " << filename << ". Error occured in " << __FILE__ << " on line " << std::to_string(__LINE__) << std::endl;
	}
	sound.setBuffer(buffer);
}

/// \brief
/// Play loaded sound.
/// \details
/// This plays the sound loaded in the buffer.
void Sound::playSound(){
	sound.play();

}

/// \brief
/// Create an instance
/// \details
/// This loads the music from the file into the sf::Music object.
Music::Music(const std::string & filename):
	filename(filename)
{
	if(!music.openFromFile(filename)){
		std::cerr << "(!)-- Error loading music in file " << filename << ". Error occured in " << __FILE__ << " on line " << std::to_string(__LINE__) << std::endl;
	}
}

/// \brief
/// Play loaded music.
/// \details
/// This plays the currently loaded music.
void Music::playMusic(){
	music.setLoop(true);

	music.play();
}

/// \brief
/// Pause loaded music.
/// \details
/// This pauses the currently loaded music.
void Music::pauseMusic(){
	music.pause();
}

/// \brief
/// Stop loaded music.
/// \details
/// This stops the currently loaded music.
void Music::stopMusic(){
	music.stop();
}

/// \brief
/// Change volume.
/// \details
/// This selects the volume of the currently playing music.
void Music::setMusicVolume(const float & newVolume){
	music.setVolume(newVolume);
}