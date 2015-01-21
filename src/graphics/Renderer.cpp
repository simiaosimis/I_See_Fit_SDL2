#include "graphics/Renderer.h"
#include <cassert>
#include "util/Configuration.h"
#include "core/Logger.h"

Renderer::Renderer(SDL_Window* const sdlWindow_, const Uint32 flags_) :
	sdlRenderer(nullptr)
{
	this->sdlRenderer = SDL_CreateRenderer(sdlWindow_, -1, flags_);
	if(this->sdlRenderer == nullptr){
		logger::error() << "Renderer could not be created. " << SDL_GetError();
	}
}

Renderer::~Renderer() {
	if(this->sdlRenderer != nullptr) {
		SDL_DestroyRenderer(this->sdlRenderer);
	}
}

void Renderer::clear() {
	const int setColor = SDL_SetRenderDrawColor(this->sdlRenderer, 0x00, 0x00, 0x00, 0xFF);
	if(setColor != 0){
		logger::error() << "Failed to set renderer draw color. " << SDL_GetError();
	}

	const int clearRenderer = SDL_RenderClear(this->sdlRenderer);
	if(clearRenderer != 0){
		logger::error() << "Failed to clear the renderer. " << SDL_GetError();
	}
}

void Renderer::render() {
	SDL_RenderPresent(this->sdlRenderer);
}

void Renderer::setLogicalSize(int size_) {
	assert(size_ >= 0 && "Must be >= 0");

	// Just a precaution, so there is no abuse on the size.
	const int safeSize = 10;
	assert(size_ < safeSize && "Trying to set logical size for a value too big.");

	const int setSize = SDL_RenderSetLogicalSize(this->sdlRenderer,
		Configuration::ResolutionWidth() * size_, Configuration::ResolutionHeight() * size_);

	if(setSize != 0) {
		logger::error() << "Failed to set the renderer logical size. " << SDL_GetError();
	}
}

void Renderer::getLogicalSize(int* w, int* h) {
	SDL_RenderGetLogicalSize(this->sdlRenderer, w, h);

	if((*w) == 0 && (*h) == 0) {
		logger::warn() << "Tried to get logical size of renderer, but it has never been set.";
	}
}

SDL_Renderer* Renderer::getSdlRenderer() {
	return this->sdlRenderer;
}
