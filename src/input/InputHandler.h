#pragma once

#include <SDL2/SDL.h>
#include "input/InputKeys.h"

namespace sdl2engine {

class InputHandler {

	public:
		/**
		* @return EventHandler::m_key_states
		*/
		static InputArray KeyStates();

		static void Reset();

		/**
		*
		*/
		static void HandleInput(const SDL_Event& sdl_event);

	private:
		static InputArray m_key_states; /**< Boolean array that controls which keys are
			pressed or not. */
};

} // namespace sdl2engine
