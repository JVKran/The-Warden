/// @file

#ifndef __AUDIO_HPP
#define __AUDIO_HPP

#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <vector>

/// \brief
/// Audio
/// \details
/// This class implements a very fast way to play audible sounds. They're buffered in cache
/// and thus very fast. This also is it's weakest point; the files can't be too large.
class Sound{
	private:
		sf::SoundBuffer buffer;				//!< The Buffer in which the sound is stored.
		sf::Sound sound;					//!< The Sound that should play after calling playSound().
		const std::string & filename;		//!< The filename of the sound that should play.
	public:
		Sound(const std::string & filename);
		void playSound();
};

/// \brief
/// Music
/// \details
/// This class implements a very fast way to play audible sounds. They're buffered in cache
/// and thus very fast. This also is it's weakest point; the files can't be too large.
class Music{
	private:
		sf::Music music;					//!< The Music that should play after calling playSound().
		const std::string & filename;		//!< The filename of the music that should play.
	public:
		Music(const std::string & filename);
		void playMusic();
		void pauseMusic();
		void stopMusic();

		void setMusicVolume(const float & newVolume);
};

#endif //__AUDIO_HPP