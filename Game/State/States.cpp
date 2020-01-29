#include "States.hpp"

void MenuState::handleInput(StateDependantObjects & objects, ViewObjects & viewObjects){
}

void MenuState::display(StateDependantObjects & objects, ViewObjects & viewObjects) {
	objects.interface.display(viewObjects.view);
}

void MenuState::handleEvent(StateDependantObjects & objects, ViewObjects & viewObjects) {
	objects.interface.handleEvent(viewObjects.event, viewObjects.view);
}

//-----------------------------------------------------------------------------------------------------------------//

void PlayingState::handleInput(StateDependantObjects & objects, ViewObjects & viewObjects){
	objects.interface.handleInput();
	objects.game.handleInput(viewObjects.view, viewObjects.event);
}

void PlayingState::display(StateDependantObjects & objects, ViewObjects & viewObjects) {

	objects.game.display(viewObjects.view);
}

void PlayingState::handleEvent(StateDependantObjects & objects, ViewObjects & viewObjects) {
	objects.game.handleEvent(viewObjects.event, viewObjects.view);
}
//-----------------------------------------------------------------------------------------------------------------//

void PauseState::handleInput(StateDependantObjects & objects, ViewObjects & viewObjects){
	objects.interface.pauseSettings(viewObjects.event, viewObjects.view);
}

void PauseState::display(StateDependantObjects & objects, ViewObjects & viewObjects) {
	objects.interface.display(viewObjects.view);
}

void PauseState::handleEvent(StateDependantObjects & objects, ViewObjects & viewObjects) {
}

//-----------------------------------------------------------------------------------------------------------------//

void EditingState::handleInput(StateDependantObjects & objects, ViewObjects & viewObjects) {
	objects.interface.handleInput();
	objects.editor.handleInput(viewObjects.view);
}

void EditingState::display(StateDependantObjects & objects, ViewObjects & viewObjects)  {
	objects.editor.draw(viewObjects.view);
}

void EditingState::handleEvent(StateDependantObjects & objects, ViewObjects & viewObjects) {
	objects.editor.handleEvent(viewObjects.event, viewObjects.view);
}

//-----------------------------------------------------------------------------------------------------------------//

void SettingsState::handleInput(StateDependantObjects & objects, ViewObjects & viewObjects){
	objects.settings.handleInput();
}

void SettingsState::display(StateDependantObjects & objects, ViewObjects & viewObjects) {
	objects.settings.draw(viewObjects.view);
}

void SettingsState::handleEvent(StateDependantObjects & objects, ViewObjects & viewObjects) {
	objects.settings.handleEvent(viewObjects.event);
}

