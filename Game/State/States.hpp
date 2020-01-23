#ifndef __STATE_HPP
#define __STATE_HPP

#include "StateMachine.hpp"

class StateMachine;
struct StateDependantObjects;
struct ViewObjects;

class State {
	public:
		virtual void handleInput(StateDependantObjects & objects, ViewObjects & viewObjects) = 0;
		virtual void handleEvent(StateDependantObjects & objects, ViewObjects & viewObjects) = 0;
		virtual void display(StateDependantObjects & objects, ViewObjects & viewObjects) = 0;
};

class MenuState : public State {
	public:
		virtual void handleInput(StateDependantObjects & objects, ViewObjects & viewObjects) override;
		virtual void handleEvent(StateDependantObjects & objects, ViewObjects & viewObjects) override;
		virtual void display(StateDependantObjects & objects, ViewObjects & viewObjects) override ;
};

class PlayingState : public State {
	public:
		virtual void handleInput(StateDependantObjects & objects, ViewObjects & viewObjects) override;
		virtual void handleEvent(StateDependantObjects & objects, ViewObjects & viewObjects) override;
		virtual void display(StateDependantObjects & objects, ViewObjects & viewObjects) override ;
};

class EditingState : public State {
	public:
		virtual void handleInput(StateDependantObjects & objects, ViewObjects & viewObjects) override;
		virtual void handleEvent(StateDependantObjects & objects, ViewObjects & viewObjects) override;
		virtual void display(StateDependantObjects & objects, ViewObjects & viewObjects) override ;
};

class SettingsState : public State {
	public:
		virtual void handleInput(StateDependantObjects & objects, ViewObjects & viewObjects) override;
		virtual void handleEvent(StateDependantObjects & objects, ViewObjects & viewObjects) override;
		virtual void display(StateDependantObjects & objects, ViewObjects & viewObjects) override ;
};

#endif //__STATE_HPP