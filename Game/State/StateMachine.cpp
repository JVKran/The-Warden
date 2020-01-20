#include "StateMachine.hpp"

void MenuState::handleInput(Game & game, Interface & interface, Editor & editor, const sf::Event & event, sf::View & view, StateMachine * machine){
	interface.handleInput(event, machine);
}

void MenuState::display(Game & game, Interface & interface, Editor & editor, const sf::Event & event, sf::View & view, StateMachine * machine) {
	interface.display();
}

void PlayingState::handleInput(Game & game, Interface & interface, Editor & editor, const sf::Event & event, sf::View & view, StateMachine * machine){
	//interface.handleInput(event, machine);
	game.handleInput(event);
}

void PlayingState::display(Game & game, Interface & interface, Editor & editor, const sf::Event & event, sf::View & view, StateMachine * machine) {
	game.display(view);
}

void EditingState::handleInput(Game & game, Interface & interface, Editor & editor, const sf::Event & event, sf::View & view, StateMachine * machine) {
	//interface.handleInput(event, machine);
	editor.handleInput(event, view);
}

void EditingState::display(Game & game, Interface & interface, Editor & editor, const sf::Event & event, sf::View & view, StateMachine * machine)  {
	editor.draw(view);
}

StateMachine::StateMachine(Game & game, Interface & interface, Editor & editor):
	game(game),
	interface(interface),
	editor(editor),
	currentState(std::make_shared<MenuState>())
{}

void StateMachine::changeState(std::shared_ptr<State> newState){
	currentState = newState;
}

std::shared_ptr<State> StateMachine::getCurrentState(){
	return currentState;
}

void StateMachine::handleInput(const sf::Event & event, sf::View & view){
	currentState->handleInput(game, interface, editor, event, view, this);
}

void StateMachine::display(const sf::Event & event, sf::View & view){
	currentState->display(game, interface, editor, event, view, this);
}
