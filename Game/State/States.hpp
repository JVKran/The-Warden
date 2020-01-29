/// @file
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
/// \brief
/// MenuState
/// \details
/// This will handle all menu events, inputs and displays it.
class MenuState : public State {
	public:
		virtual void handleInput(StateDependantObjects & objects, ViewObjects & viewObjects) override;
		virtual void handleEvent(StateDependantObjects & objects, ViewObjects & viewObjects) override;
		virtual void display(StateDependantObjects & objects, ViewObjects & viewObjects) override ;
		virtual int getName() override {
			return 1;
		}
};
/// \brief
/// PlayingState
/// \details
/// This will handle all playing events, inputs and displays it.
class PlayingState : public State {
	public:
		virtual void handleInput(StateDependantObjects & objects, ViewObjects & viewObjects) override;
		virtual void handleEvent(StateDependantObjects & objects, ViewObjects & viewObjects) override;
		virtual void display(StateDependantObjects & objects, ViewObjects & viewObjects) override ;
		virtual int getName() override {
			return 2;
		}
};
/// \brief
/// PauseState
/// \details
/// This will handle all pause events, inputs and displays it.
class PauseState : public State {
	public:
		virtual void handleInput(StateDependantObjects & objects, ViewObjects & viewObjects) override;
		virtual void handleEvent(StateDependantObjects & objects, ViewObjects & viewObjects) override;
		virtual void display(StateDependantObjects & objects, ViewObjects & viewObjects) override ;
		virtual int getName() override {
			return 3;
		}
};
/// \brief
/// EditingState
/// \details
/// This will handle all editing events, inputs and displays it.
class EditingState : public State {
	public:
		virtual void handleInput(StateDependantObjects & objects, ViewObjects & viewObjects) override;
		virtual void handleEvent(StateDependantObjects & objects, ViewObjects & viewObjects) override;
		virtual void display(StateDependantObjects & objects, ViewObjects & viewObjects) override ;
		virtual int getName() override {
			return 4;
		}
};
/// \brief
/// SettingState
/// \details
/// This will handle all setting events, inputs and displays it.
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