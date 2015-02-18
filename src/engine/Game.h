#pragma once

#include <SDL2/SDL.h>
#include <memory>
#include <string>
#include "engine/StateManager.h"
#include "graphics/Window.h"
#include "graphics/Renderer.h"
#include "input/EventHandler.h"

namespace sdl2engine {

/**
* @brief Main structure class for the game.
*
* Contains all the necessary functionalities to loop and update the game.
*
* @note Is a Singleton.
*/
class Game {

	private:
		struct ConstructorTag {}; /**< Private tag needed to use the constructor. */

	public:
		/**
		* @brief Singleton implementation for Game.
		*
		* @return The instance for a Game.
		*/
		static Game& Instance();

		/**
		* @brief The constructor.
		*
		* Since the std::make_unique in Game::Instance() can't access a private constructor,
		* we make this constructor public but need a ConstructorTag parameter. ConstructorTag
		* is an empty struct only accessible by this class, since it is private. This way the
		* constructor can only actually be used in a private setting.
		*/
		explicit Game(const ConstructorTag& private_tag);

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
		void ChangeState(const GameStates game_state);

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
		* @brief Resizes the window.
		*/
		void ResizeWindow(const int width, const int height);

	private:
		bool m_is_running; /**< Whether the game is currently running/looping or not. */
		EventHandler m_event_handler; /**< The Game EventHandler. */
		Window m_window; /**< The game Window. */
		StateManager m_state_manager;
};

} // namespace sdl2engine
