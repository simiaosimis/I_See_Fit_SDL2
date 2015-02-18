#include "input/EventHandler.h"
#include <SDL2/SDL.h>
#include "input/InputHandler.h"
#include "util/Logger.h"

namespace sdl2engine {

EventHandler::EventHandler() :
	m_quit_flagged{false}
{
}

void EventHandler::PollEvents() {

	SDL_Event sdl_event;
	int pending_event = 0;
	InputHandler::Reset();

	do {

		pending_event = SDL_PollEvent(&sdl_event);

		switch(sdl_event.type) {
			// Application event;
			case SDL_QUIT:
				m_quit_flagged = true;
				break;

			// Window events.
			case SDL_WINDOWEVENT:
				break;
			case SDL_SYSWMEVENT:
				break;

			// Keyboard events.
			case SDL_KEYDOWN: // Fallthrough
			case SDL_KEYUP:
				InputHandler::HandleInput(sdl_event);
				break;
			case SDL_TEXTEDITING:
				break;
			case SDL_TEXTINPUT:
				break;

			// Mouse events.
			case SDL_MOUSEMOTION:
				break;
			case SDL_MOUSEBUTTONDOWN:
				break;
			case SDL_MOUSEBUTTONUP:
				break;
			case SDL_MOUSEWHEEL:
				break;

			// Joystick events.
			case SDL_JOYAXISMOTION:
				log_warn() << "SDL_JOYAXISMOTION event!";
				break;
			case SDL_JOYBALLMOTION:
				log_warn() << "SDL_JOYBALLMOTION event!";
				break;
			case SDL_JOYHATMOTION:
				log_warn() << "SDL_JOYHATMOTION event!";
				break;
			case SDL_JOYBUTTONDOWN:
				log_warn() << "SDL_JOYBUTTONDOWN event!";
				break;
			case SDL_JOYBUTTONUP:
				log_warn() << "SDL_JOYBUTTONUP event!";
				break;
			case SDL_JOYDEVICEADDED:
				log_warn() << "SDL_JOYDEVICEADDED event!";
				break;
			case SDL_JOYDEVICEREMOVED:
				log_warn() << "SDL_JOYDEVICEREMOVED event!";
				break;

			// Controller events.
			case SDL_CONTROLLERAXISMOTION:
				break;
			case SDL_CONTROLLERBUTTONDOWN:
				break;
			case SDL_CONTROLLERBUTTONUP:
				break;
			case SDL_CONTROLLERDEVICEADDED:
				break;
			case SDL_CONTROLLERDEVICEREMOVED:
				break;
			case SDL_CONTROLLERDEVICEREMAPPED:
				break;

			default:
				break;
		}

	} while(pending_event != 0);
}

bool EventHandler::QuitFlagged() {
	return m_quit_flagged;
}

} // namespace sdl2engine
