#include "engine/Game.h"
#include <chrono>
#include <memory>
#include "util/Configuration.h"
#include "graphics/Sprite.h"
#include "util/Logger.h"
#include "util/Assert.h"
// Begin Game States includes
#include "engine/GStatePlaceholder.h"
// End Game States includes

#define ADD_STATE(stateEnum, stateClass) \
	m_game_states.insert(std::make_pair(stateEnum, new stateClass()))

namespace sdl2engine {

Game& Game::Instance() {
	// "C++11 mandates that the initializer for a local static variable is only run once, even
	// in the presence of concurrency. So, assuming you’ve got a modern C++ compiler, this code
	// is thread-safe[...]"
	static std::unique_ptr<Game> instance{new Game};
	return *instance.get();
}

Game::Game() :
	m_is_running{false},
	m_audio_handler{new AudioHandler()},
	m_input_handler{new InputHandler()},
	m_resource_handler{new ResourceHandler()},
	m_current_state{nullptr},
	m_window{},
	m_game_states{}
{
	InitializeStates();
	m_is_running = true;
}

Game::~Game() {
	if(m_current_state != nullptr) {
		m_current_state->unload();
	}

	DestroyStates();

	delete m_audio_handler;
	delete m_input_handler;
	delete m_resource_handler;
}

void Game::Run() {
	// Load the first state of the game.
	m_current_state = m_game_states.at(GStates::PLACEHOLDER);
	m_current_state->load();

	// Get the first game time.
	const double deltaTime = 1.0 / 60.0;
	double totalGameTime = 0.0;
	double accumulatedTime = 0.0;

	using s_clock = std::chrono::steady_clock;
	s_clock::time_point lastTime = s_clock::now();

	// This is the main game loop.
	while(m_is_running) {

#ifdef ICYTIMEDRUN
		// Auto-close the game in 2 seconds so TravisCI doesn't loop forever
		if(totalGameTime >= 2.0) {
			m_is_running = false;
		}
#endif

		s_clock::time_point now = s_clock::now();
		s_clock::duration dt{now - lastTime};

		const double frameTime = std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1, 1>>>(dt).count();
		accumulatedTime += frameTime;

		// Update.
		while(accumulatedTime >= deltaTime) {
			m_input_handler->handleInput();

			// Check for an exit signal from input.
			if(m_input_handler->isQuitFlag() == true) {
				Stop();
				return;
			}

			m_current_state->update(deltaTime);

			accumulatedTime -= deltaTime;
			totalGameTime += deltaTime;
		}

		// Render.
		m_window.GetRenderer()->Clear();
		m_current_state->render();
		m_window.GetRenderer()->Render();

		lastTime = now;

	}

}

void Game::ChangeState(const GStates game_state) {
	/// @todo Implement the transition between states.
	m_current_state->unload();
	m_current_state = m_game_states.at(game_state);
	m_current_state->load();
}

void Game::InitializeStates() {
	// Initialize all the states in Game here.

	// Insert the states pointers onto the map.
	/// @todo Emplace instead of insert.
	ADD_STATE(PLACEHOLDER, GStatePlaceholder);
}

void Game::DestroyStates() {
	StatesMap::const_iterator it;
    for(it = m_game_states.begin(); it != m_game_states.end(); it++) {
        delete it->second;
    }
}

AudioHandler& Game::GetAudioHandler() {
	return (*(m_audio_handler));
}

InputArray Game::Input() {
	return m_input_handler->getKeyStates();
}

void Game::Stop() {
	m_is_running = false;
}

void Game::ClearInputKey(const GameKeys input_key) {
	m_input_handler->clearKey(input_key);
}

void Game::ResizeWindow(const int width, const int height) {
	ASSERT(width >= 0 , "Must be >= 0");
	ASSERT(height >= 0, "Must be >= 0");
	m_window.Resize(width, height);
}

Renderer* Game::GetRenderer() {
	return m_window.GetRenderer();
}

ResourceHandler& Game::Resource() {
	return (*(m_resource_handler));
}

} // namespace sdl2engine

#undef ADD_STATE
