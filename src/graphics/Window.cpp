#include "graphics/Window.h"
#include <cassert>
#include "util/Logger.h"
#include "util/Configuration.h"

Window::Window() :
	m_sdl_window(nullptr),
	m_renderer(nullptr)
{
	Create();
}

Window::~Window() {
	delete m_renderer;

	if(m_sdl_window != nullptr) {
		SDL_DestroyWindow(m_sdl_window);
	}
}

void Window::Minimize() {
	SDL_MinimizeWindow(m_sdl_window);
}

void Window::Maximize() {
	SDL_MaximizeWindow(m_sdl_window);
}

void Window::Create() {
	/// @todo Toggle VSync.

	// Creates the SDL window.
	const Uint32 windowFlags = SDL_WINDOW_SHOWN;
	m_sdl_window = SDL_CreateWindow(Configuration::WindowTitle(), SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, Configuration::ScreenWidth(), Configuration::ScreenHeight(),
		windowFlags);

	if(m_sdl_window != nullptr) {

		// Creates the SDL renderer.
		const Uint32 rendererFlags = SDL_RENDERER_ACCELERATED;
		m_renderer = new Renderer(m_sdl_window, rendererFlags);

		if(m_renderer != nullptr) {

			// Set texture filtering to linear.
			SDL_bool linearFilter = SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

			if(linearFilter == SDL_TRUE) {
				log_info() << "Linear texture filtering enabled!";
				m_renderer->SetLogicalSize(Configuration::LogicalRenderSize());
			}
			else {
				log_warn() << "Linear texture filtering disabled!";
			}

			log_debug() << "Game successfully loaded.";

		}
		else {
			log_error() << "Renderer could not be created, while creating window. " <<
				SDL_GetError();
		}
	}
	else {
		log_error() << "Window failed to be created. " << SDL_GetError();
	}
}

void Window::Resize(const int width_, const int height_) {
	assert(width_ >= 0 && "Must be >= 0");
	assert(height_ >= 0 && "Must be >= 0");
	SDL_SetWindowSize(m_sdl_window, width_, height_);
}

Renderer* Window::GetRenderer() {
	return m_renderer;
}
