#pragma once

#include <SDL2/SDL.h>
#include <map>
#include <memory>
#include <string>
#include "graphics/Window.h"
#include "engine/StateGame.h"
#include "audio/AudioHandler.h"
#include "input/InputHandler.h"
#include "engine/ResourceHandler.h"

/**
* Main structure class for the game.
* Contains all the necessary functionalities to loop and update the game.
* 	Is the state machine (controls current state), contains all the different possible states.
*/
class Game {

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
		* @briefSets the current game state.
		*
		* @see StateGame::load()
		* @see StateGame::unload()
		*
		* @param game_state : The state you want to be changed into.
		*/
		void ChangeState(const GStates game_state);

		/**
		* @return The Game audio handler.
		*
		* @note The 'Get' was added to the name to avoid conflict with class AudioHandler.
		*/
		AudioHandler& GetAudioHandler();

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
		* @return The Game resource handler.
		*/
		ResourceHandler& Resource();

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
		* The constructor.
		* Sets the game window and tells the game that it is OK to begin looping. Also, it
		* 	begins the FPS manager.
		* @note If the Window cannot be created, the game will not begin.
		*/
		Game();

		/**
		* Loads all the states.
		* Every new state implemented should be initialized here.
		*/
		void InitializeStates();

		/**
		* Deletes all the loaded states.
		* Every new state implemented should be deleted here.
		*/
		void DestroyStates();

		bool m_is_running; /**< Whether the game is currently running/looping or not. */
		AudioHandler* m_audio_handler; /**< The Game AudioHandler. */
		InputHandler* m_input_handler; /**< The Game InputHandler. */
		ResourceHandler* m_resource_handler; /**< The Game ResourceHandler. */
		StateGame* m_current_state; /**< The current state, which the game is in. */
		Window m_window; /**< The game Window. */

		using StatesMap = std::map<GStates, StateGame*>;
		StatesMap m_game_states; /**< Map containing all possible states. */

};
