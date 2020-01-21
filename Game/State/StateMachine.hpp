#ifndef __STATEMACHINE_HPP
#define __STATEMACHINE_HPP

#include <memory>
#include "Game.hpp"
#include "Interface.hpp"
#include "Editor.hpp"

class Interface;
class StateMachine;

class State {
	public:
		virtual void handleInput(Game & game, Interface & interface, Editor & editor, const sf::Event & event, sf::View & view, StateMachine * machine) = 0;
		virtual void handleEvent(Game & game, Interface & interface, Editor & editor, const sf::Event & event, sf::View & view, StateMachine * machine) = 0;
		virtual void display(Game & game, Interface & interface, Editor & editor, const sf::Event & event, sf::View & view, StateMachine * machine) = 0;
};

class MenuState : public State {
	public:
		virtual void handleInput(Game & game, Interface & interface, Editor & editor, const sf::Event & event, sf::View & view, StateMachine * machine) override;
		virtual void handleEvent(Game & game, Interface & interface, Editor & editor, const sf::Event & event, sf::View & view, StateMachine * machine) override;
		virtual void display(Game & game, Interface & interface, Editor & editor, const sf::Event & event, sf::View & view, StateMachine * machine) override ;
};

class PlayingState : public State {
	public:
		virtual void handleInput(Game & game, Interface & interface, Editor & editor, const sf::Event & event, sf::View & view, StateMachine * machine) override;
		virtual void handleEvent(Game & game, Interface & interface, Editor & editor, const sf::Event & event, sf::View & view, StateMachine * machine) override;
		virtual void display(Game & game, Interface & interface, Editor & editor, const sf::Event & event, sf::View & view, StateMachine * machine) override;
};

class EditingState : public State {
	public:
		virtual void handleInput(Game & game, Interface & interface, Editor & editor, const sf::Event & event, sf::View & view, StateMachine * machine) override;
		virtual void handleEvent(Game & game, Interface & interface, Editor & editor, const sf::Event & event, sf::View & view, StateMachine * machine) override;
		virtual void display(Game & game, Interface & interface, Editor & editor, const sf::Event & event, sf::View & view, StateMachine * machine) override;
};

class StateMachine {
	private:
		Game & game;
		Interface & interface;
		Editor & editor;

		std::shared_ptr<State> currentState;
	public:
		StateMachine(Game & game, Interface & interface, Editor & editor);

		void changeState(std::shared_ptr<State> newState);

		std::shared_ptr<State> getCurrentState();

		void handleInput(const sf::Event & event, sf::View & view);
		void handleEvent(const sf::Event & event, sf::View & view);
		void display(const sf::Event & event, sf::View & view);
};

#endif //__STATEMACHING_HPP