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
/// This will display all menu sprites.
void MenuState::display(StateDependantObjects & objects, ViewObjects & viewObjects) {
	objects.interface.display(viewObjects.view);
}
/// \brief
/// MenuState handle input.
/// \details
/// This handles all the events it gets; used for starting a game, the editor or closing the window.
void MenuState::handleEvent(StateDependantObjects & objects, ViewObjects & viewObjects) {
	objects.interface.handleEvent(viewObjects.event, viewObjects.view);
}

//-----------------------------------------------------------------------------------------------------------------//
/// \brief
/// PlayingState handle input.
/// \details
/// This handles the escape button, that shows the pause state and the previous state.
/// It will also handle all player inputs.
void PlayingState::handleInput(StateDependantObjects & objects, ViewObjects & viewObjects){
	objects.interface.handleInput();
	objects.game.handleInput(viewObjects.view, viewObjects.event);
}
/// \brief
/// PlayingState handle input.
/// \details
/// This will display the game.
void PlayingState::display(StateDependantObjects & objects, ViewObjects & viewObjects) {

	objects.game.display(viewObjects.view);
}
/// \brief
/// PlayingState handle input.
/// \details
/// This handles all character handleable occured events.
void PlayingState::handleEvent(StateDependantObjects & objects, ViewObjects & viewObjects) {
	objects.game.handleEvent(viewObjects.event, viewObjects.view);
}
//-----------------------------------------------------------------------------------------------------------------//
/// \brief
/// PauseState handle input.
/// \details
/// This will enable the pause menu to be clickable.
void PauseState::handleInput(StateDependantObjects & objects, ViewObjects & viewObjects){
	objects.interface.pauseSettings(viewObjects.event, viewObjects.view);
}
/// \brief
/// pauseState handle display.
/// \details
/// This will display all the pause state sprites.
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
/// This handles the escape button, that shows the pause state and the previous state.
/// It will also handle all player inputs.
void EditingState::handleInput(StateDependantObjects & objects, ViewObjects & viewObjects) {
	objects.interface.handleInput();
	objects.editor.handleInput(viewObjects.view);
}
/// \brief
/// EditingState handle display.
/// \details
/// This will display the editable world and the tile scrollbar.
void EditingState::display(StateDependantObjects & objects, ViewObjects & viewObjects)  {
	objects.editor.draw(viewObjects.view);
}
/// \brief
/// EditingState handle event.
/// \details
/// This will handle if any event based actions have to be performed.
void EditingState::handleEvent(StateDependantObjects & objects, ViewObjects & viewObjects) {
	objects.editor.handleEvent(viewObjects.event, viewObjects.view);
}

//-----------------------------------------------------------------------------------------------------------------//
/// \brief
/// SettingState handle input.
/// \details
/// This will handle the back button color.
void SettingsState::handleInput(StateDependantObjects & objects, ViewObjects & viewObjects){
	objects.settings.handleInput();
}
/// \brief
/// SettingState handle display.
/// \details
/// This will display all needed sprites and texts.
void SettingsState::display(StateDependantObjects & objects, ViewObjects & viewObjects) {
	objects.settings.draw(viewObjects.view);
}
/// \brief
/// SettingState handle event.
/// \details
/// This will handle the key changes.
void SettingsState::handleEvent(StateDependantObjects & objects, ViewObjects & viewObjects) {
	objects.settings.handleEvent(viewObjects.event);
}

