#ifndef __AUDIO_HPP
#define __AUDIO_HPP

#include <SFML/Audio.hpp>
#include <string>
#include <vector>

class Sound{
	private:
		sf::SoundBuffer buffer;
		sf::Sound sound;
		const std::string & filename;
	public:
		Sound(const std::string & filename);
		void playSound();
};

class Music{
	private:
		sf::Music music;
		const std::string & filename;
	public:
		Music(const std::string & filename);
		void playMusic();
		void pauseMusic();
		void stopMusic();

		void setMusicVolume(const float & newVolume);
};

#endif //Audio.hpp