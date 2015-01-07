#include "Game.h"
#include "Configuration.h"
#include "Util.h"
#include "Sprite.h"
#include "Logger.h"

// Begin Game States includes
#include "GStatePlaceholder.h"
// End Game States includes

#include <cassert>
#include <chrono>

#define ADD_STATE_EMPLACE(stateEnum, stateClass) \
	this->statesMap.emplace(stateEnum, new stateClass())

#define ADD_STATE_INSERT(stateEnum, stateClass) \
	this->statesMap.insert(std::make_pair(stateEnum, new stateClass()))

Game& Game::instance() {
	// "C++11 mandates that the initializer for a local static variable is only run once, even
	// in the presence of concurrency. So, assuming you’ve got a modern C++ compiler, this code
	// is thread-safe[...]"
	static Game* instance = new Game();
	return (*instance);
}

Game::Game() :
	window(nullptr),
	isRunning(false),
	audioHandler(new AudioHandler()),
	inputHandler(new InputHandler()),
	resourceHandler(new ResourceHandler()),
	currentState(nullptr),
	statesMap()
{
	this->window = new Window(Configuration::getScreenWidth(),
		Configuration::getScreenHeight(), Configuration::getWindowTitle());

	assert(this->window != nullptr && "The window should not be null!");

	initializeStates();

	this->isRunning = true;
}

Game::~Game() {
	if(this->currentState != nullptr) {
		this->currentState->unload();
	}

	destroyStates();

	delete this->audioHandler;
	delete this->inputHandler;
	delete this->resourceHandler;
	delete this->window;
}

void Game::runGame() {
	// Load the first state of the game.
	this->currentState = this->statesMap.at(GStates::PLACEHOLDER);
	this->currentState->load();

	// Get the first game time.
	const double deltaTime = 1.0 / 60.0;
	double totalGameTime = 0.0;
	double accumulatedTime = 0.0;

	using s_clock = std::chrono::steady_clock;
	s_clock::time_point lastTime = s_clock::now();

	// This is the main game loop.
	while(this->isRunning) {

#ifdef ICYTIMEDRUN
		// Auto-close the game in 2 seconds so TravisCI doesn't loop forever
		if(totalGameTime >= 2.0) {
			this->isRunning = false;
		}
#endif

		s_clock::time_point now = s_clock::now();
		s_clock::duration dt{now - lastTime};

		const double frameTime = std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1, 1>>>(dt).count();
		accumulatedTime += frameTime;

		// Update.
		while(accumulatedTime >= deltaTime) {
			this->inputHandler->handleInput();

			// Check for an exit signal from input.
			if(this->inputHandler->isQuitFlag() == true) {
				stop();
				return;
			}

			this->currentState->update(deltaTime);

			accumulatedTime -= deltaTime;
			totalGameTime += deltaTime;
		}

		// Render.
		this->window->getRenderer()->clear();
		this->currentState->render();
		this->window->getRenderer()->render();

		lastTime = now;

	}

}

void Game::changeState(const GStates state_) {
	/// @todo Implement the transition between states.
	this->currentState->unload();
	this->currentState = this->statesMap.at(state_);
	this->currentState->load();
}

void Game::initializeStates() {
	// Initialize all the states in Game here.

	// Emplace the states pointers onto the map.
	ADD_STATE_INSERT(PLACEHOLDER, GStatePlaceholder);
}

void Game::destroyStates() {
	std::map<GStates, StateGame*>::const_iterator it;
    for(it = this->statesMap.begin(); it != this->statesMap.end(); it++) {
        delete it->second;
    }
}

AudioHandler& Game::getAudioHandler() {
	return (*(this->audioHandler));
}

std::array<bool, GameKeys::MAX> Game::getInput() {
	return this->inputHandler->getKeyStates();
}

void Game::stop() {
	this->isRunning = false;
}

void Game::clearKeyFromInput(const GameKeys key_) {
	this->inputHandler->clearKey(key_);
}

void Game::resizeWindow(const unsigned int width_, const unsigned int height_) {
	this->window->resize(width_, height_);
}

Renderer* Game::getRenderer() {
	return this->window->getRenderer();
}

ResourceHandler& Game::getResource() {
	return (*(this->resourceHandler));
}
