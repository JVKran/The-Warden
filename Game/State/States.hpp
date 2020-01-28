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

		virtual int getName() = 0;
};

class MenuState : public State {
	public:
		virtual void handleInput(StateDependantObjects & objects, ViewObjects & viewObjects) override;
		virtual void handleEvent(StateDependantObjects & objects, ViewObjects & viewObjects) override;
		virtual void display(StateDependantObjects & objects, ViewObjects & viewObjects) override ;
		virtual int getName() override {
			return 1;
		}
};

class PlayingState : public State {
	public:
		virtual void handleInput(StateDependantObjects & objects, ViewObjects & viewObjects) override;
		virtual void handleEvent(StateDependantObjects & objects, ViewObjects & viewObjects) override;
		virtual void display(StateDependantObjects & objects, ViewObjects & viewObjects) override ;
		virtual int getName() override {
			return 2;
		}
};

class PauseState : public State {
	public:
		virtual void handleInput(StateDependantObjects & objects, ViewObjects & viewObjects) override;
		virtual void handleEvent(StateDependantObjects & objects, ViewObjects & viewObjects) override;
		virtual void display(StateDependantObjects & objects, ViewObjects & viewObjects) override ;
		virtual int getName() override {
			return 3;
		}
};

class EditingState : public State {
	public:
		virtual void handleInput(StateDependantObjects & objects, ViewObjects & viewObjects) override;
		virtual void handleEvent(StateDependantObjects & objects, ViewObjects & viewObjects) override;
		virtual void display(StateDependantObjects & objects, ViewObjects & viewObjects) override ;
		virtual int getName() override {
			return 4;
		}
};

class SettingsState : public State {
	public:
		virtual void handleInput(StateDependantObjects & objects, ViewObjects & viewObjects) override;
		virtual void handleEvent(StateDependantObjects & objects, ViewObjects & viewObjects) override;
		virtual void display(StateDependantObjects & objects, ViewObjects & viewObjects) override ;
		virtual int getName() override {
			return 5;
		}
};

#endif //__STATE_HPP