#ifndef __GAME_HPP
#define __GAME_HPP

class Game {
	private:
		AssetManager assets;

		sf::RenderWindow window{ sf::VideoMode{ 1000, 580 }, "The Warden", sf::Style::Resize};
		sf::View view(sf::FloatRect(0.f, 0.f, 1000.f, 580.f));
	public:
		Game(const std::string & objectConfigurationFile);

		void handleInput();
};


#endif //__GAME_HPP