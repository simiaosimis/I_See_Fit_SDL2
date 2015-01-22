#include "graphics/Renderer.h"
#include <cassert>
#include "util/Configuration.h"
#include "util/Logger.h"

Renderer::Renderer(SDL_Window* const sdl_window, const Uint32 flags) :
	m_sdl_renderer{SDL_CreateRenderer(sdl_window, -1, flags)}
{
	if(m_sdl_renderer == nullptr){
		logger::error() << "Renderer could not be created. " << SDL_GetError();
	}
}

Renderer::~Renderer() {
	if(m_sdl_renderer != nullptr) {
		SDL_DestroyRenderer(m_sdl_renderer);
	}
}

void Renderer::Clear() {
	const int k_set_color = SDL_SetRenderDrawColor(m_sdl_renderer, 0x00, 0x00, 0x00, 0xFF);
	if(k_set_color != 0){
		logger::error() << "Failed to set renderer draw color. " << SDL_GetError();
	}

	const int k_clear_renderer = SDL_RenderClear(m_sdl_renderer);
	if(k_clear_renderer != 0){
		logger::error() << "Failed to clear the renderer. " << SDL_GetError();
	}
}

void Renderer::Render() {
	SDL_RenderPresent(m_sdl_renderer);
}

void Renderer::SetLogicalSize(const int size) {
	assert(size >= 0 && "Must be >= 0");

	// Just a precaution, so there is no abuse on the size.
	const int k_safe_size = 10;
	assert(size < k_safe_size && "Trying to set logical size for a value too big (>= 10).");

	const int k_set_size = SDL_RenderSetLogicalSize(m_sdl_renderer,
		Configuration::ResolutionWidth() * size, Configuration::ResolutionHeight() * size);

	if(k_set_size != 0) {
		logger::error() << "Failed to set the renderer logical size. " << SDL_GetError();
	}
}

void Renderer::LogicalSize(int* width, int* height) {
	SDL_RenderGetLogicalSize(m_sdl_renderer, width, height);

	if((*width) == 0 && (*height) == 0) {
		logger::warn() << "Tried to get logical size of renderer, but it has never been set.";
	}
}

SDL_Renderer* Renderer::SdlRenderer() {
	return m_sdl_renderer;
}
