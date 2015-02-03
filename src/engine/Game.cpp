#include "engine/Game.h"
#include <chrono>
#include <memory>
#include "engine/Timer.h"
#include "graphics/Sprite.h"
#include "util/Configuration.h"
#include "util/Logger.h"
#include "util/Assert.h"
// Begin Game States includes
#include "engine/GStatePlaceholder.h"
// End Game States includes

namespace sdl2engine {

Game& Game::Instance() {
	// "C++11 mandates that the initializer for a local static variable is only run once, even
	// in the presence of concurrency. So, assuming you’ve got a modern C++ compiler, this code
	// is thread-safe[...]"
	static auto instance = std::make_unique<Game>(ConstructorTag{});
	return *instance.get();
}

Game::Game(const ConstructorTag& private_tag) :
	m_is_running{false},
	m_input_handler{std::make_unique<InputHandler>()},
	m_current_state{nullptr},
	m_window{},
	m_game_states{}
{
	static_cast<void>(private_tag);
	InitializeStates();
	m_is_running = true;
}

Game::~Game() {
	if(m_current_state != nullptr) {
		m_current_state->unload();
	}
}

void Game::Run() {
	// Load the first state of the game.
	m_current_state = m_game_states.at(GStates::PLACEHOLDER).get();
	ASSERT(m_current_state != nullptr, "Some game state should be loaded.");
	m_current_state->load();

	// Get the first game time.
	const auto k_delta_time = 1.0 / 60.0;
	auto total_game_time = 0.0;
	auto accumulated_time = 0.0;

	/////////////////////////////// CREATE TIMER (LAST_TIME = CLOCK::NOW)
	Timer timer{};

	// This is the main game loop.
	while(m_is_running) {

#ifdef ICYTIMEDRUN
		// Auto-close the game in 2 seconds so TravisCI doesn't loop forever
		if(total_game_time >= 2.0) {
			m_is_running = false;
		}
#endif

		accumulated_time += timer.GetFrameTime();

		// Update.
		while(accumulated_time >= k_delta_time) {
			m_input_handler->handleInput();

			// Check for an exit signal from input.
			if(m_input_handler->isQuitFlag() == true) {
				Stop();
				return;
			}

			m_current_state->update(k_delta_time);

			accumulated_time -= k_delta_time;
			total_game_time += k_delta_time;
		}

		// Render.
		m_window.GetRenderer()->Clear();
		m_current_state->render();
		m_window.GetRenderer()->Render();

		//////////////////////////////////////// RESET
		timer.Reset();
	}

}

void Game::ChangeState(const GStates game_state) {
	/// @todo Implement the transition between states.
	m_current_state->unload();
	m_current_state = m_game_states.at(game_state).get();
	m_current_state->load();
}

void Game::InitializeStates() {
#define ADD_STATE(GSTATE_ENUM, GStateClass) m_game_states.emplace((GSTATE_ENUM), \
	(std::make_unique<GStateClass>()))

	// Add all the states in Game here.
	ADD_STATE(PLACEHOLDER, GStatePlaceholder);

#undef ADD_STATE
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

} // namespace sdl2engine
