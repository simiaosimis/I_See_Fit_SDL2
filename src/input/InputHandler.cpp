#include "input/InputHandler.h"

namespace sdl2engine {

InputArray InputHandler::m_key_states;

InputArray InputHandler::KeyStates() {
	return m_key_states;
}

void InputHandler::Reset() {
	m_key_states.fill(false);
}

void InputHandler::HandleInput(const SDL_Event& sdl_event) {
	const bool key_up = (sdl_event.type == SDL_KEYUP);
	const bool key_down_no_repeat =
		(sdl_event.type == SDL_KEYDOWN && sdl_event.key.repeat == 0);

	if(key_down_no_repeat || key_up) {
		switch(sdl_event.key.keysym.sym) {
			case SDLK_f:
				m_key_states[Key::FadeOut] = key_down_no_repeat;
				break;
			case SDLK_l:
				m_key_states[Key::LogSomething] = key_down_no_repeat;
				break;
			case SDLK_s:
				m_key_states[Key::TestSfx] = key_down_no_repeat;						
				break;
			case SDLK_a:
				m_key_states[Key::TestSfxAfterFadeOut] = key_down_no_repeat;						
				break;
			case SDLK_ESCAPE:
				m_key_states[Key::Quit] = key_down_no_repeat;
				break;
			default:
				break;
		}
	}
}

} // namespace sdl2engine
