#include "StateMachine.hpp"

void MenuState::handleInput(Game & game, Interface & interface, Editor & editor, Settings & settings, const sf::Event & event, sf::View & view, StateMachine * machine){
	interface.handleInput(machine);
}

void MenuState::display(Game & game, Interface & interface, Editor & editor, Settings & settings, const sf::Event & event, sf::View & view, StateMachine * machine) {
	interface.display();
}

void MenuState::handleEvent(Game & game, Interface & interface, Editor & editor, Settings & settings, const sf::Event & event, sf::View & view, StateMachine * machine) {
	interface.handleEvent(event, machine);
}

void PlayingState::handleInput(Game & game, Interface & interface, Editor & editor, Settings & settings, const sf::Event & event, sf::View & view, StateMachine * machine){
	game.handleInput();
}

void PlayingState::display(Game & game, Interface & interface, Editor & editor, Settings & settings, const sf::Event & event, sf::View & view, StateMachine * machine) {
	game.display(view);
}

void PlayingState::handleEvent(Game & game, Interface & interface, Editor & editor, Settings & settings, const sf::Event & event, sf::View & view, StateMachine * machine) {
}



void EditingState::handleInput(Game & game, Interface & interface, Editor & editor, Settings & settings, const sf::Event & event, sf::View & view, StateMachine * machine) {
	//interface.handleInput(event, machine);
	editor.handleInput(view);
}

void EditingState::display(Game & game, Interface & interface, Editor & editor, Settings & settings, const sf::Event & event, sf::View & view, StateMachine * machine)  {
	editor.draw(view);
}

void EditingState::handleEvent(Game & game, Interface & interface, Editor & editor, Settings & settings, const sf::Event & event, sf::View & view, StateMachine * machine) {
}

void SettingsState::handleInput(Game & game, Interface & interface, Editor & editor, Settings & settings, const sf::Event & event, sf::View & view, StateMachine * machine) {
	settings.handleInput();
}

void SettingsState::display(Game & game, Interface & interface, Editor & editor, Settings & settings, const sf::Event & event, sf::View & view, StateMachine * machine) {
	settings.draw();
}

void SettingsState::handleEvent(Game & game, Interface & interface, Editor & editor, Settings & settings, const sf::Event & event, sf::View & view, StateMachine * machine) {
	settings.handleEvent(event, machine);
}

StateMachine::StateMachine(Game & game, Interface & interface, Editor & editor, Settings & settings):
	game(game),
	interface(interface),
	editor(editor),
	settings(settings),
	currentState(std::make_shared<MenuState>())
{}

void StateMachine::changeState(std::shared_ptr<State> newState){
	currentState = newState;
}

std::shared_ptr<State> StateMachine::getCurrentState(){
	return currentState;
}

void StateMachine::handleInput(const sf::Event & event, sf::View & view){
	currentState->handleInput(game, interface, editor, settings, event, view, this);
}

void StateMachine::handleEvent(const sf::Event & event, sf::View & view){
	currentState->handleEvent(game, interface, editor, settings, event, view, this);
}

void StateMachine::display(const sf::Event & event, sf::View & view){
	currentState->display(game, interface, editor, settings, event, view, this);
}
