#include "Window.h"
#include <cassert>
#include "Logger.h"
#include "Configuration.h"

Window::Window(const int width_, const int height_, const std::string& title_) :
	windowTitle(title_),
	sdlWindow(nullptr),
	renderer(nullptr)
{
	assert(width_ >= 0 && "Must be >= 0");
	assert(height_ >= 0 && "Must be >= 0");
	create(width_, height_);
}

Window::~Window() {
	delete this->renderer;
	if(this->sdlWindow != nullptr) {
		SDL_DestroyWindow(this->sdlWindow);
	}
}

void Window::minimize() {
	SDL_MinimizeWindow(this->sdlWindow);
}

void Window::maximize() {
	SDL_MaximizeWindow(this->sdlWindow);
}

void Window::create(const int width_, const int height_) {
	/// @todo Toggle VSync.
	assert(width_ >= 0 && "Must be >= 0");
	assert(height_ >= 0 && "Must be >= 0");

	// Creates the SDL window.
	const Uint32 windowFlags = SDL_WINDOW_SHOWN;
	this->sdlWindow = SDL_CreateWindow(this->windowTitle.c_str(), SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, width_, height_, windowFlags);

	if(this->sdlWindow != nullptr) {

		// Creates the SDL renderer.
		const Uint32 rendererFlags = SDL_RENDERER_ACCELERATED;
		this->renderer = new Renderer(this->sdlWindow, rendererFlags);

		if(this->renderer != nullptr) {

			// Set texture filtering to linear.
			SDL_bool linearFilter = SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

			if(linearFilter == SDL_TRUE) {
				logger::info() << "Linear texture filtering enabled!";
				this->renderer->setLogicalSize(Configuration::LogicalRenderSize());
			}
			else {
				logger::warn() << "Linear texture filtering disabled!";
			}

			logger::debug() << "Game successfully loaded.";

		}
		else {
			logger::error() << "Renderer could not be created, while creating window. " <<
				SDL_GetError();
		}
	}
	else {
		logger::error() << "Window failed to be created. " << SDL_GetError();
	}
}

void Window::resize(const int width_, const int height_) {
	assert(width_ >= 0 && "Must be >= 0");
	assert(height_ >= 0 && "Must be >= 0");
	SDL_SetWindowSize(this->sdlWindow, width_, height_);
}

Renderer* Window::getRenderer() {
	return this->renderer;
}
