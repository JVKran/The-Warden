#include "StateMachine.hpp"

StateMachine::StateMachine(Game & game, Interface & interface, Editor & editor, Settings & settings, sf::View & view):
	stateDependantObjects(game, interface, editor, settings),
	view(view),
	currentState(std::make_shared<MenuState>())
{ 
	interface.initialize(this); 
	settings.initialize(this);
}


void StateMachine::changeState(std::shared_ptr<State> newState){
	currentState = newState;
	switch(currentState->getName()){
		case 1:{ // Menu
			
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
			backgroundMusic.pauseMusic();
			editingMusic.pauseMusic();
			break;
		}
	}
	std::cout << prevState << "\n";

	if( prevState==4){
		editPosition = view.getCenter();
		std::cout << editPosition.x << " : " << editPosition.y << "\n";
	}
}


std::shared_ptr<State> StateMachine::getCurrentState(){
	return currentState;
}

void StateMachine::handleInput(const sf::Event & event){
	ViewObjects viewObjects(view, event);
	currentState->handleInput(stateDependantObjects, viewObjects);
}

void StateMachine::handleEvent(const sf::Event & event){
	ViewObjects viewObjects(view, event);
	currentState->handleEvent(stateDependantObjects, viewObjects);
}

void StateMachine::display(const sf::Event & event){
	ViewObjects viewObjects(view, event);
	currentState->display(stateDependantObjects, viewObjects);
}