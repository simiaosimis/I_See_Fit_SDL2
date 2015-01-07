#include "Renderer.h"
#include "Configuration.h"
#include "Logger.h"

Renderer::Renderer(SDL_Window* const sdlWindow_, const Uint32 flags_) :
	sdlRenderer(nullptr)
{
	this->sdlRenderer = SDL_CreateRenderer(sdlWindow_, -1, flags_);
	if(this->sdlRenderer == nullptr){
		Log(ERROR) << "Renderer could not be created. " << SDL_GetError();
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
		Log(ERROR) << "Failed to set renderer draw color. " << SDL_GetError();
	}

	const int clearRenderer = SDL_RenderClear(this->sdlRenderer);
	if(clearRenderer != 0){
		Log(ERROR) << "Failed to clear the renderer. " << SDL_GetError();
	}
}

void Renderer::render() {
	SDL_RenderPresent(this->sdlRenderer);
}

void Renderer::setLogicalSize(unsigned int size_) {
	// Just a precaution, so there is no abuse on the size.
	const unsigned int safeSize = 10;

	if(size_ > safeSize) {
		size_ = safeSize;
		Log(WARN) << "Trying to set logical size for a value too big.";
	}

	const int setSize = SDL_RenderSetLogicalSize(this->sdlRenderer,
		Configuration::getResolutionWidth() * size_,
		Configuration::getResolutionHeight() * size_);

	if(setSize != 0) {
		Log(ERROR) << "Failed to set the renderer logical size. " << SDL_GetError();
	}
}

void Renderer::getLogicalSize(int* w, int* h) {
	SDL_RenderGetLogicalSize(this->sdlRenderer, w, h);

	if((*w) == 0 && (*h) == 0) {
		Log(WARN) << "Tried to get logical size of renderer, but it has never been set.";
	}
}

SDL_Renderer* Renderer::getSdlRenderer() {
	return this->sdlRenderer;
}
