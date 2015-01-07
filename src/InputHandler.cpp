#include "InputHandler.h"
#include "Logger.h"

InputHandler::InputHandler() :
	controllerHandler(new ControllerHandler()),
	quitFlag(false)
{
	this->keyStates.fill(false);
}

InputHandler::~InputHandler() {
	delete this->controllerHandler;
}

void InputHandler::handleInput() {

	int pendingEvent = 0;

	do {

		pendingEvent = SDL_PollEvent(&this->sdlEvent);

		if(this->sdlEvent.type == SDL_CONTROLLERBUTTONDOWN
			|| this->sdlEvent.type == SDL_CONTROLLERBUTTONUP
			|| this->sdlEvent.type == SDL_CONTROLLERAXISMOTION) {

			this->controllerHandler->handleInput(this->sdlEvent);

			for(unsigned int i = 0; i < this->keyStates.size(); i++) {
				this->keyStates[i] = this->controllerHandler->getKeyStates()[i];
			}

		}
		// On keydown.
		if(this->sdlEvent.type == SDL_KEYDOWN) {

			switch(this->sdlEvent.key.keysym.sym) {
				case SDLK_SPACE: // SPACEBAR.
					this->keyStates[GameKeys::SPACE] = true;
					break;
				case SDLK_UP: // UP ARROW.
					this->keyStates[GameKeys::UP] = true;
					break;
				case SDLK_DOWN: // DOWN ARROW.
					this->keyStates[GameKeys::DOWN] = true;
					break;
				case SDLK_LEFT: // LEFT ARROW.
					this->keyStates[GameKeys::LEFT] = true;
					break;
				case SDLK_RIGHT: // RIGHT ARROW.
					this->keyStates[GameKeys::RIGHT] = true;
					break;
				case SDLK_ESCAPE: // ESCAPE.
					this->keyStates[GameKeys::ESCAPE] = true;
					break;
				default:
					break;
			}
		}

		// On keyup.
		else if(this->sdlEvent.type == SDL_KEYUP) {

			switch(this->sdlEvent.key.keysym.sym) {
				case SDLK_SPACE: // SPACEBAR.
					this->keyStates[GameKeys::SPACE] = false;
					break;
				case SDLK_UP: // UP ARROW.
					this->keyStates[GameKeys::UP] = false;
					break;
				case SDLK_DOWN: // DOWN ARROW.
					this->keyStates[GameKeys::DOWN] = false;
					break;
				case SDLK_LEFT: // LEFT ARROW.
					this->keyStates[GameKeys::LEFT] = false;
					break;
				case SDLK_RIGHT: // RIGHT ARROW.
					this->keyStates[GameKeys::RIGHT] = false;
					break;
				case SDLK_ESCAPE: // ESCAPE.
					this->keyStates[GameKeys::ESCAPE] = false;
					break;
				default:
					break;
			}
		}

		// On window exit (X).
		else if(this->sdlEvent.type == SDL_QUIT) {
			signalExit();
		}

	} while(pendingEvent != 0);
}

std::array<bool, GameKeys::MAX> InputHandler::getKeyStates() {
	return this->keyStates;
}

bool InputHandler::isQuitFlag() {
	return this->quitFlag;
}

void InputHandler::signalExit() {
	this->quitFlag = true;
}

void InputHandler::clearKey(const GameKeys key_) {
	this->keyStates.at(key_) = false;
}
