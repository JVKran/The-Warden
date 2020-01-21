#ifndef __STATE_HPP
#define __STATE_HPP

#include "StateMachine.hpp"

class StateMachine;
struct StateDependantObjects;
struct ViewObjects;

class State {
	public:
		virtual void handleInput(StateDependantObjects & objects, ViewObjects & viewObjects, StateMachine * machine) = 0;
		virtual void handleEvent(StateDependantObjects & objects, ViewObjects & viewObjects, StateMachine * machine) = 0;
		virtual void display(StateDependantObjects & objects, ViewObjects & viewObjects, StateMachine * machine) = 0;
};

class MenuState : public State {
	public:
		virtual void handleInput(StateDependantObjects & objects, ViewObjects & viewObjects, StateMachine * machine) override;
		virtual void handleEvent(StateDependantObjects & objects, ViewObjects & viewObjects, StateMachine * machine) override;
		virtual void display(StateDependantObjects & objects, ViewObjects & viewObjects, StateMachine * machine) override ;
};

class PlayingState : public State {
	public:
		virtual void handleInput(StateDependantObjects & objects, ViewObjects & viewObjects, StateMachine * machine) override;
		virtual void handleEvent(StateDependantObjects & objects, ViewObjects & viewObjects, StateMachine * machine) override;
		virtual void display(StateDependantObjects & objects, ViewObjects & viewObjects, StateMachine * machine) override;
};

class EditingState : public State {
	public:
		virtual void handleInput(StateDependantObjects & objects, ViewObjects & viewObjects, StateMachine * machine) override;
		virtual void handleEvent(StateDependantObjects & objects, ViewObjects & viewObjects, StateMachine * machine) override;
		virtual void display(StateDependantObjects & objects, ViewObjects & viewObjects, StateMachine * machine) override;
};

class SettingsState : public State {
	public:
		virtual void handleInput(StateDependantObjects & objects, ViewObjects & viewObjects, StateMachine * machine) override;
		virtual void handleEvent(StateDependantObjects & objects, ViewObjects & viewObjects, StateMachine * machine) override;
		virtual void display(StateDependantObjects & objects, ViewObjects & viewObjects, StateMachine * machine) override;
};

#endif //__STATE_HPP