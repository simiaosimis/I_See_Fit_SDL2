#include "engine/Game.h"
#include <chrono>
#include <memory>
#include "engine/Timer.h"
#include "graphics/Sprite.h"
#include "util/Configuration.h"
#include "util/Logger.h"
#include "util/Assert.h"

namespace sdl2engine {

Game& Game::Instance() {
	// "C++11 mandates that the initializer for a local static variable is only run once, even
	// in the presence of concurrency. So, assuming you’ve got a modern C++ compiler, this code
	// is thread-safe[...]"
	static auto instance = std::make_unique<Game>(ConstructorTag{});
	return *instance.get();
}

Game::Game(const ConstructorTag& private_tag) :
	m_is_running{true},
	m_event_handler{},
	m_window{},
	m_state_manager{}
{
	static_cast<void>(private_tag);
}

void Game::Run() {
	// Load the first state of the game.
	m_state_manager.LoadFirstState();

	// Get the first game time.
	const auto k_delta_time = 1.0 / 60.0;
	auto total_game_time = 0.0;
	auto accumulated_time = 0.0;

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
			m_event_handler.PollEvents();

			// Check for an exit signal from input.
			if(m_event_handler.QuitFlagged() == true) {
				Stop();
				return;
			}

			m_state_manager.CurrentState()->Update(k_delta_time);

			accumulated_time -= k_delta_time;
			total_game_time += k_delta_time;
		}

		// Render.
		m_window.GetRenderer()->Clear();
		m_state_manager.CurrentState()->Render();
		m_window.GetRenderer()->Render();

		timer.Reset();
	}

}

void Game::ChangeState(const GameStates game_state) {
	/// @todo Implement the transition between states.
	m_state_manager.ChangeState(game_state);
}

void Game::Stop() {
	m_is_running = false;
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
