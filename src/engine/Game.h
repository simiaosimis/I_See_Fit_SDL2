#pragma once

#include <SDL2/SDL.h>
#include <map>
#include <memory>
#include <string>
#include "graphics/Window.h"
#include "graphics/Renderer.h"
#include "engine/StateGame.h"
#include "input/InputHandler.h"

namespace sdl2engine {

/**
* Main structure class for the game.
* Contains all the necessary functionalities to loop and update the game.
* 	Is the state machine (controls current state), contains all the different possible states.
*/
class Game {

	private:
		struct ConstructorTag {} /**< Private tag needed to use the constructor. */;

	public:
		/**
		* All possible game states.
		*/
		enum GStates : uint8_t {
			PLACEHOLDER = 0
		};

		/**
		* @brief Singleton implementation for Game.
		*
		* @return The instance for a Game.
		*/
		static Game& Instance();

		/**
		* @brief The constructor.
		*
		* Sets the game window and tells the game that it is OK to begin looping.
		* Since the std::make_unique in Game::Instance() can't access a private constructor,
		* we make this constructor public but need a ConstructorTag parameter. ConstructorTag
		* is an empty struct only accessible by this class, since it is private. This way the
		* constructor can only actually be used in a private setting.
		*/
		explicit Game(const ConstructorTag& private_tag);

		/**
		* @brief The destructor.
		*
		* Destroys the game's Window and states, and unloads current state.
		*/
		~Game();

		/**
		* @brief The main game loop.
		*
		* Orders the game structure, such as inputs, updates, and rendering.
		*/
		void Run();

		/**
		* @brief Sets the current game state.
		*
		* @see StateGame::load()
		* @see StateGame::unload()
		*
		* @param game_state : The state you want to be changed into.
		*/
		void ChangeState(const GStates game_state);

		/**
		* @return The boolean array recieved from the InputHandler.
		*/
		InputArray Input();

		/**
		* @return The SDL_Renderer.
		*
		* @note The 'Get' was added to the name to avoid conflict with class Renderer.
		*/
		Renderer* GetRenderer();

		/**
		* @brief Stops execution and closes the game.
		*/
		void Stop();

		/**
		* @brief Clears a certain key from input, setting it to false.
		*/
		void ClearInputKey(const GameKeys input_key);

		/**
		* @brief Resizes the window.
		*/
		void ResizeWindow(const int width, const int height);

	private:
		/**
		* Loads all the states.
		* Every new state implemented should be initialized here.
		*/
		void InitializeStates();

		bool m_is_running; /**< Whether the game is currently running/looping or not. */
		std::unique_ptr<InputHandler> m_input_handler; /**< The Game InputHandler. */
		StateGame* m_current_state; /**< The current state, which the game is in. */
		Window m_window; /**< The game Window. */

		using StatesMap = std::map<GStates, std::unique_ptr<StateGame>>;
		StatesMap m_game_states; /**< Map containing all possible states. */
};

} // namespace sdl2engine
