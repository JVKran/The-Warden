///@file
#include "StateMachine.hpp"
/// \brief
/// Statemachine constructor
/// \details
/// This is the StateMachine constructor.
/// @param stateDependantObjects This will need the game, interface, editor and settings.
/// @param view This is the view 
/// @param currentState This is the current state with a default of the menu state.
StateMachine::StateMachine(Game & game, Interface & interface, Editor & editor, Settings & settings, sf::View & view):
	stateDependantObjects(game, interface, editor, settings),
	view(view),
	currentState(std::make_shared<MenuState>())
{ 
	interface.initialize(this); 
	settings.initialize(this);
}

/// \brief
/// Change to a new state.
/// \details
/// This function will switch to the right state and play their respective code.
/// @param newState This will have the new state that needs to be changed to.
void StateMachine::changeState(std::shared_ptr<State> newState){
	currentState = newState;
	switch(currentState->getName()){
		case 1:{ // Menu
			editingMusic.pauseMusic();
			backgroundMusic.pauseMusic();
			prevState = 1;
			break;
		}
		case 2: { // Game
			backgroundMusic.playMusic();
			editingMusic.pauseMusic();
			prevState = 2;
			break;
		}
		case 4: { // Editor
			backgroundMusic.pauseMusic();
			editingMusic.playMusic();
			prevState = 4;
			std::cout << "here\n";
			view.setCenter(editPosition);
			break;
		}
		case 5: { // Settings
			prevState = 5;
			break;
		}
		default: {
			// Don't add prevState here;
			break;
		}
	}
	if( prevState==4){
		editPosition = view.getCenter();
	}
}

/// \brief
/// Return currentState.
/// \details
/// This will return what the current state is.
/// \return A std::shared_ptr of the current state.
std::shared_ptr<State> StateMachine::getCurrentState(){
	return currentState;
}

/// \brief
/// Handle input.
/// \details
/// This handles the handle inputs of the currentState.
void StateMachine::handleInput(const sf::Event & event){
	ViewObjects viewObjects(view, event);
	currentState->handleInput(stateDependantObjects, viewObjects);
}

//// \brief
/// Handle event.
/// \details
/// This handles the handle events of the currentState.
void StateMachine::handleEvent(const sf::Event & event){
	ViewObjects viewObjects(view, event);
	currentState->handleEvent(stateDependantObjects, viewObjects);
}

/// \brief
/// Display the state.
/// \details
/// This displays the current state of the game on screen.
void StateMachine::display(const sf::Event & event){
	ViewObjects viewObjects(view, event);
	currentState->display(stateDependantObjects, viewObjects);
}