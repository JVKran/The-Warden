#ifndef __STATEMACHINE_HPP
#define __STATEMACHINE_HPP

#include <memory>
#include "Game.hpp"
#include "Interface.hpp"
#include "Editor.hpp"
#include "Settings.hpp"
#include "States.hpp"

class Game;
class Interface;
class StateMachine;


class Settings;
class State;

struct StateDependantObjects {
	Game & game;
	Interface & interface;
	Editor & editor;
	Settings & settings;

	StateDependantObjects(Game & game, Interface & interface, Editor & editor, Settings & settings):
		game(game),
		interface(interface),
		editor(editor),
		settings(settings)
	{}
};

struct ViewObjects {
	sf::View & view;
	const sf::Event & event;

	ViewObjects(sf::View & view, const sf::Event & event):
		view(view),
		event(event)
	{}
};

class StateMachine {
	private:
		StateDependantObjects stateDependantObjects;
		Music backgroundMusic = Music("background.wav");
		Music editingMusic = Music("editingBackground.wav");

		std::shared_ptr<State> currentState;
	public:
		StateMachine(Game & game, Interface & interface, Editor & editor, Settings & settings);

		void changeState(std::shared_ptr<State> newState);
		
		std::shared_ptr<State> getCurrentState();
		void handleInput(const sf::Event & event, sf::View & view);
		void handleEvent(const sf::Event & event, sf::View & view);
		void display(const sf::Event & event, sf::View & view);
};

#endif //__STATEMACHING_HPP