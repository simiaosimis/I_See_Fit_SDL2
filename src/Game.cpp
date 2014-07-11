#include "Game.h"
#include "FPSWrapper.h"
#include "Configuration.h"
#include "Util.h"
#include "Sprite.h"
#include "Logger.h"
#include "UsefulDefines.h"
#include <cassert>

#include "GStatePlaceholder.h"

#define ADD_STATE_EMPLACE(stateEnum, stateClass) this->statesMap.emplace(stateEnum, new stateClass())
#define ADD_STATE_INSERT(stateEnum, stateClass) this->statesMap.insert(std::make_pair<GStates, StateGame*>(stateEnum, new stateClass()))

Game& Game::instance(){
	static Game* instance = new Game();
	return *instance;
}

Game::Game() :
	window(nullptr),
	isRunning(false),
	audioHandler(new AudioHandler()),
	inputHandler(new InputHandler()),
	resourceManager(new SpriteManager()),
	currentState(nullptr),
	statesMap()
{
	this->window = new Window(Configuration::getScreenWidth(),
		Configuration::getScreenHeight(), Configuration::getWindowTitle());

	assert(this->window != nullptr && "The window should not be null!");

	initializeStates();

	this->isRunning = true;
	FPSWrapper::initialize(this->fpsManager);
}

Game::~Game(){
	if(this->currentState != nullptr){
		this->currentState->unload();
	}

	destroyStates();

	SAFE_DELETE(audioHandler);
	SAFE_DELETE(inputHandler);
	SAFE_DELETE(resourceManager);
	SAFE_DELETE(window);
}

void Game::runGame(){
	// Load the first state of the game.
	this->currentState = this->statesMap.at(GStates::PLACEHOLDER);
	this->currentState->load();

	// Get the first game time.
	double totalGameTime = 0.0;
	const double deltaTime = 1.0 / 60.0;
	double accumulatedTime = 0.0;

	// This is the main game loop.
	while(this->isRunning){

		const double frameTime = FPSWrapper::delay(this->fpsManager);
		accumulatedTime += frameTime;

		// Update.
		while(accumulatedTime >= deltaTime){
			this->inputHandler->handleInput();

			// Check for an exit signal from input.
			if(this->inputHandler->isQuitFlag() == true){
				stop();
				return;
			}

			this->currentState->update(deltaTime);

			accumulatedTime -= deltaTime;
			totalGameTime += deltaTime;
		}

		// Render.
		window->clear();
		
		this->currentState->render();				    

		window->render();
		
	}

}

void Game::changeState(const GStates state_){
	/// @todo Implement the transition between states.
	this->currentState->unload();
	this->currentState = this->statesMap.at(state_);
	this->currentState->load();
}

void Game::initializeStates(){
	// Initialize all the states in Game here.

	// Emplace the states pointers onto the map.
	ADD_STATE_INSERT(PLACEHOLDER, GStatePlaceholder);
}

void Game::destroyStates(){
	std::map<GStates, StateGame*>::const_iterator it;
    for(it = this->statesMap.begin(); it != this->statesMap.end(); it++){
        delete it->second;
    }
}

AudioHandler& Game::getAudioHandler(){
	return (*(this->audioHandler));
}

std::array<bool, GameKeys::MAX> Game::getInput(){
	return this->inputHandler->getKeyStates();
}

SpriteManager& Game::getResources(){
	return (*(this->resourceManager));
}

void Game::stop(){
	this->isRunning = false;
}

void Game::clearKeyFromInput(const GameKeys key_){
	this->inputHandler->clearKey(key_);
}

void Game::resizeWindow(const unsigned int width_, const unsigned int height_){
	this->window->resize(width_, height_);
}
