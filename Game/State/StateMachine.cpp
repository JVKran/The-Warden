#include "StateMachine.hpp"

void MenuState::handleInput(Game & game, Interface & interface, Editor & editor, const sf::Event & event, sf::View & view){
	interface.handleInput();
}

void MenuState::display(Game & game, Interface & interface, Editor & editor, const sf::Event & event, sf::View & view) {
	interface.display();
}

void MenuState::handleEvent(Game & game, Interface & interface, Editor & editor, const sf::Event & event, sf::View & view) {
	interface.handleEvent(event);
}



void PlayingState::handleInput(Game & game, Interface & interface, Editor & editor, const sf::Event & event, sf::View & view){
	game.handleInput();
}

void PlayingState::display(Game & game, Interface & interface, Editor & editor, const sf::Event & event, sf::View & view) {
	game.display(view);
}

void PlayingState::handleEvent(Game & game, Interface & interface, Editor & editor, const sf::Event & event, sf::View & view) {
}



void EditingState::handleInput(Game & game, Interface & interface, Editor & editor, const sf::Event & event, sf::View & view) {
	//interface.handleInput(event, machine);
	editor.handleInput(view);
}

void EditingState::display(Game & game, Interface & interface, Editor & editor, const sf::Event & event, sf::View & view)  {
	editor.draw(view);
}

void EditingState::handleEvent(Game & game, Interface & interface, Editor & editor, const sf::Event & event, sf::View & view) {
	editor.handleEvent(event, view);
}

StateMachine::StateMachine(Game & game, Interface & interface, Editor & editor):
	game(game),
	interface(interface),
	editor(editor),
	currentState(std::make_shared<MenuState>())
{ 
	interface.initialize(this); 
}

void StateMachine::changeState(std::shared_ptr<State> newState){
	currentState = newState;
}

std::shared_ptr<State> StateMachine::getCurrentState(){
	return currentState;
}

void StateMachine::handleInput(const sf::Event & event, sf::View & view){
	currentState->handleInput(game, interface, editor, event, view);
}

void StateMachine::handleEvent(const sf::Event & event, sf::View & view){
	currentState->handleEvent(game, interface, editor, event, view);
}

void StateMachine::display(const sf::Event & event, sf::View & view){
	currentState->display(game, interface, editor, event, view);
}
