#include "StateMachine.hpp"

void MenuState::handleInput(StateDependantObjects & objects, ViewObjects & viewObjects, StateMachine * machine){
	objects.interface.handleInput(machine);
}

void MenuState::display(StateDependantObjects & objects, ViewObjects & viewObjects, StateMachine * machine) {
	objects.interface.display();
}

void MenuState::handleEvent(StateDependantObjects & objects, ViewObjects & viewObjects, StateMachine * machine) {
	objects.interface.handleEvent(viewObjects.event, machine);
}

void PlayingState::handleInput(StateDependantObjects & objects, ViewObjects & viewObjects, StateMachine * machine){
	objects.game.handleInput();
}

void PlayingState::display(StateDependantObjects & objects, ViewObjects & viewObjects, StateMachine * machine) {
	objects.game.display(viewObjects.view);
}

void PlayingState::handleEvent(StateDependantObjects & objects, ViewObjects & viewObjects, StateMachine * machine) {
}



void EditingState::handleInput(StateDependantObjects & objects, ViewObjects & viewObjects, StateMachine * machine) {
	//interface.handleInput(event, machine);
	objects.editor.handleInput(viewObjects.view);
}

void EditingState::display(StateDependantObjects & objects, ViewObjects & viewObjects, StateMachine * machine)  {
	objects.editor.draw(viewObjects.view);
}

void EditingState::handleEvent(StateDependantObjects & objects, ViewObjects & viewObjects, StateMachine * machine) {
	objects.editor.handleEvent(viewObjects.event, viewObjects.view);
}

void SettingsState::handleInput(StateDependantObjects & objects, ViewObjects & viewObjects, StateMachine * machine) {
	objects.settings.handleInput();
}

void SettingsState::display(StateDependantObjects & objects, ViewObjects & viewObjects, StateMachine * machine) {
	objects.settings.draw();
}

void SettingsState::handleEvent(StateDependantObjects & objects, ViewObjects & viewObjects, StateMachine * machine) {
	objects.settings.handleEvent(viewObjects.event, machine);
}

StateMachine::StateMachine(Game & game, Interface & interface, Editor & editor, Settings & settings):
	stateDependantObjects(game, interface, editor, settings),
	currentState(std::make_shared<MenuState>())
{}

void StateMachine::changeState(std::shared_ptr<State> newState){
	currentState = newState;
}

std::shared_ptr<State> StateMachine::getCurrentState(){
	return currentState;
}

void StateMachine::handleInput(const sf::Event & event, sf::View & view){
	ViewObjects viewObjects(view, event);
	currentState->handleInput(stateDependantObjects, viewObjects, this);
}

void StateMachine::handleEvent(const sf::Event & event, sf::View & view){
	ViewObjects viewObjects(view, event);
	currentState->handleEvent(stateDependantObjects, viewObjects, this);
}

void StateMachine::display(const sf::Event & event, sf::View & view){
	ViewObjects viewObjects(view, event);
	currentState->display(stateDependantObjects, viewObjects, this);
}
