#ifndef __GAME_HPP
#define __GAME_HPP

#include <string>

class Game {
	private:
		AssetManager assets;
		std::vector<std::string> worldConfigurationFiles;

		World world;

		sf::RenderWindow window{ sf::VideoMode{ 1000, 580 }, "The Warden", sf::Style::Resize};
		sf::View view(sf::FloatRect(0.f, 0.f, 1000.f, 580.f));
	public:
		Game(const std::string & objectConfigurationFile, const std::vector<std::string> & worldFileNames = ("World/world.txt"));

		void handleInput();

		void startWorld(const std::string & worldName);

		void draw();
};


#endif //__GAME_HPP