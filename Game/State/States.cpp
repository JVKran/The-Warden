#include "States.hpp"

void MenuState::handleInput(StateDependantObjects & objects, ViewObjects & viewObjects, StateMachine * machine){
	objects.interface.handleInput(machine);
}

void MenuState::display(StateDependantObjects & objects, ViewObjects & viewObjects, StateMachine * machine) {
	objects.interface.display();
}

void MenuState::handleEvent(StateDependantObjects & objects, ViewObjects & viewObjects, StateMachine * machine) {
	objects.interface.handleEvent(viewObjects.event, machine);
}

//-----------------------------------------------------------------------------------------------------------------//

void PlayingState::handleInput(StateDependantObjects & objects, ViewObjects & viewObjects, StateMachine * machine){
	objects.game.handleInput();
}

void PlayingState::display(StateDependantObjects & objects, ViewObjects & viewObjects, StateMachine * machine) {
	objects.game.display(viewObjects.view);
}

void PlayingState::handleEvent(StateDependantObjects & objects, ViewObjects & viewObjects, StateMachine * machine) {
}

//-----------------------------------------------------------------------------------------------------------------//

void EditingState::handleInput(StateDependantObjects & objects, ViewObjects & viewObjects, StateMachine * machine) {
	objects.editor.handleInput(viewObjects.view);
}

void EditingState::display(StateDependantObjects & objects, ViewObjects & viewObjects, StateMachine * machine)  {
	objects.editor.draw(viewObjects.view);
}

void EditingState::handleEvent(StateDependantObjects & objects, ViewObjects & viewObjects, StateMachine * machine) {
	objects.editor.handleEvent(viewObjects.event, viewObjects.view);
}

//-----------------------------------------------------------------------------------------------------------------//

void SettingsState::handleInput(StateDependantObjects & objects, ViewObjects & viewObjects, StateMachine * machine) {
	//objects.settings.addKeyBindings(objects);
	objects.settings.handleInput();
}

void SettingsState::display(StateDependantObjects & objects, ViewObjects & viewObjects, StateMachine * machine) {
	objects.settings.draw();
}

void SettingsState::handleEvent(StateDependantObjects & objects, ViewObjects & viewObjects, StateMachine * machine) {
	objects.settings.handleEvent(viewObjects.event, machine);
}