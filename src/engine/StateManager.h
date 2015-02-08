#pragma once

#include <map>
#include <memory>
#include "engine/StateGame.h"

namespace sdl2engine {

/**
* All possible game states.
*/
enum GameStates {
	PLACEHOLDER,
	TOTAL // Should always be last.
};

class StateManager {

	public:
		/**
		* @brief The constructor.
		*/
		StateManager();

		/**
		* @brief The destructor.
		*/
		~StateManager();

		// Not copyable and not moveable.
		StateManager(const StateManager&) = delete;
		StateManager& operator=(const StateManager&) = delete;
		StateManager(StateManager&&) = delete;
		StateManager& operator=(StateManager&&) = delete;

		/**
		* @brief Sets the current game state.
		*
		* @see StateGame::load()
		* @see StateGame::unload()
		*
		* @param game_state : The state you want to be changed into.
		*/
		void ChangeState(const GameStates game_state);

		/**
		* @brief Loads first state of the game.
		*/
		void LoadFirstState();

		/**
		* @return The current game state.
		*/
		StateGame* CurrentState();

	private:
		/**
		* @brief Loads all the states.
		*
		* Every new state implemented should be initialized here.
		*/
		void InitializeStates();

		StateGame* m_current_state; /**< The current state, which the game is in. */
		std::map<GameStates, std::unique_ptr<StateGame>> m_game_states; /**< Map containing all
			possible states. */
};

} // namespace sdl2engine
