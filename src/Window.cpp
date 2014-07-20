#include "Window.h"
#include "Logger.h"
#include "Configuration.h"
#include "UsefulDefines.h"

Window::Window(const unsigned int width_, const unsigned int height_, const std::string& title_) :
	windowTitle(title_),
	sdlWindow(nullptr),
	renderer(nullptr)
{
	create(width_, height_);
}

Window::~Window() {
	SAFE_DELETE(this->renderer);
	SAFE_DELETE_WITH_FUNCTION(SDL_DestroyWindow, this->sdlWindow);
}

void Window::minimize() {
	SDL_MinimizeWindow(this->sdlWindow);
}

void Window::maximize() {
	SDL_MaximizeWindow(this->sdlWindow);
}

void Window::create(const unsigned int width_, const unsigned int height_) {
	/// @todo Toggle VSync.

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
				Log(INFO) << "Linear texture filtering enabled!";
				this->renderer->setLogicalSize(Configuration::getLogicalRenderSize());
			}
			else {
				Log(WARN) << "Linear texture filtering disabled!";
			}

			Log(DEBUG) << "Game successfully loaded.";

		}
		else {
			Log(ERROR) << "Renderer could not be created, while creating window. " <<
				SDL_GetError();
		}
	}
	else {
		Log(ERROR) << "Window failed to be created. " << SDL_GetError();
	}
}

void Window::resize(const unsigned int width_, const unsigned int height_) {
	SDL_SetWindowSize(this->sdlWindow, width_, height_);
}

Renderer* Window::getRenderer() {
	return this->renderer;
}
