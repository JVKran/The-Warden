/// @file
#include "States.hpp"
/// \brief
/// MenuState handle input.
/// \details
/// Handles menustate input.
void MenuState::handleInput(StateDependantObjects & objects, ViewObjects & viewObjects){
}
/// \brief
/// MenuState handle input.
/// \details
/// Handles menustate display.
void MenuState::display(StateDependantObjects & objects, ViewObjects & viewObjects) {
	objects.interface.display(viewObjects.view);
}
/// \brief
/// MenuState handle input.
/// \details
/// Handles menustate event.
void MenuState::handleEvent(StateDependantObjects & objects, ViewObjects & viewObjects) {
	objects.interface.handleEvent(viewObjects.event, viewObjects.view);
}

//-----------------------------------------------------------------------------------------------------------------//
/// \brief
/// PlayingState handle input.
/// \details
/// Handles playingstate input.
void PlayingState::handleInput(StateDependantObjects & objects, ViewObjects & viewObjects){
	objects.interface.handleInput();
	objects.game.handleInput(viewObjects.view, viewObjects.event);
}
/// \brief
/// PlayingState handle input.
/// \details
/// Handles playingstate display.
void PlayingState::display(StateDependantObjects & objects, ViewObjects & viewObjects) {

	objects.game.display(viewObjects.view);
}
/// \brief
/// PlayingState handle input.
/// \details
/// Handles playingstate event.
void PlayingState::handleEvent(StateDependantObjects & objects, ViewObjects & viewObjects) {
	objects.game.handleEvent(viewObjects.event, viewObjects.view);
}
//-----------------------------------------------------------------------------------------------------------------//
/// \brief
/// PauseState handle input.
/// \details
/// Handles pausestate input.
void PauseState::handleInput(StateDependantObjects & objects, ViewObjects & viewObjects){
	objects.interface.pauseSettings(viewObjects.event, viewObjects.view);
}
/// \brief
/// pauseState handle display.
/// \details
/// Handles pausestate display.
void PauseState::display(StateDependantObjects & objects, ViewObjects & viewObjects) {
	objects.interface.display(viewObjects.view);
}
/// \brief
/// PauseState handle event.
/// \details
/// Handles pausestate event.
void PauseState::handleEvent(StateDependantObjects & objects, ViewObjects & viewObjects) {
}

//-----------------------------------------------------------------------------------------------------------------//
/// \brief
/// EditingState handle input.
/// \details
/// Handles EditingState input.
void EditingState::handleInput(StateDependantObjects & objects, ViewObjects & viewObjects) {
	objects.interface.handleInput();
	objects.editor.handleInput(viewObjects.view);
}
/// \brief
/// EditingState handle display.
/// \details
/// Handles EditingState display.
void EditingState::display(StateDependantObjects & objects, ViewObjects & viewObjects)  {
	objects.editor.draw(viewObjects.view);
}
/// \brief
/// EditingState handle event.
/// \details
/// Handles EditingState event.
void EditingState::handleEvent(StateDependantObjects & objects, ViewObjects & viewObjects) {
	objects.editor.handleEvent(viewObjects.event, viewObjects.view);
}

//-----------------------------------------------------------------------------------------------------------------//
/// \brief
/// SettingState handle input.
/// \details
/// Handles settingState input.
void SettingsState::handleInput(StateDependantObjects & objects, ViewObjects & viewObjects){
	objects.settings.handleInput();
}
/// \brief
/// SettingState handle display.
/// \details
/// Handles settingState display.
void SettingsState::display(StateDependantObjects & objects, ViewObjects & viewObjects) {
	objects.settings.draw(viewObjects.view);
}
/// \brief
/// SettingState handle event.
/// \details
/// Handles settingState event.
void SettingsState::handleEvent(StateDependantObjects & objects, ViewObjects & viewObjects) {
	objects.settings.handleEvent(viewObjects.event);
}

