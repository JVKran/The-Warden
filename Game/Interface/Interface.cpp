#include "Interface.hpp"

Interface::Interface(Game & game, Editor & editor, AssetManager & assets, sf::RenderWindow & window):
	game(game),
	editor(editor),
	assets(assets),
	window(window)
{}

void Interface::initialize(StateMachine * machine){
	background.setTexture(assets.getTexture("background"));
	
	interfaceElements.push_back(InterfaceElement( ScreenObject ("startButton", assets, sf::Vector2f(550,300), float(1)), Action ( [machine]{  machine->changeState(std::make_shared<PlayingState>());})));
	interfaceElements.push_back(InterfaceElement( ScreenObject ("editButton", assets, sf::Vector2f(150,300),float(0.35)), Action ( [machine]{ machine->changeState(std::make_shared<EditingState>());})));

}
void Interface::handleInput(){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
		game.startWorld("World/world.txt");
		interfaceElements[0].changeState();
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
		 editor.selectWorld("World/world.txt");
		interfaceElements[1].changeState();
	}
}

void Interface::handleEvent(const sf::Event & event){
	for( InterfaceElement & sprite : interfaceElements){
		if(sprite.contains(window)){
			if(event.type == sf::Event::MouseButtonPressed && sprite.comparePosition(sf::Vector2f(550, 300)) ){
				game.startWorld("World/world.txt");
				sprite.changeState();
			}
			if(event.type == sf::Event::MouseButtonPressed && sprite.comparePosition(sf::Vector2f(150, 300)) ){
						 editor.selectWorld("World/world.txt");
				sprite.changeState();
			}
		}
	}
}


void Interface::display(){
	window.draw(background);
	for( InterfaceElement & sprite : interfaceElements){
		sprite.draw(window);
	}
}