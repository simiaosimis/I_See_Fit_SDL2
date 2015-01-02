#pragma once

#include "SDL_Libs.h"
#include "Renderer.h"
#include <string>

/**
* Represents the actual window that the game runs on.
* Contains the SDL_Window and the SDL_Renderer, and methods related to these.
*/
class Window {

	public:
		/**
		* The constructor.
		* Sets all attributes, and calls the initialize method.
		* @param width_ : The desired window width.
		* @param height_ : The desired window height.
		* @param title_ : The desired window title.
		* @note If omitted, window title will be "SDL Window".
		* @see Window::initialize
		*/
		Window(const unsigned int width_, const unsigned int height_,
			const std::string& title_ = "SDL Window");

		/**
		* The destructor.
		* Uses the destroy method to delete window.
		* @see Window::destroy
		*/
		~Window();

		/**
		* Resizes the window.
		* @todo Instead of directly choosing width and height, choose from a pre-defined list
		* 	of resolutions.
		*/
		void resize(const unsigned int width_, const unsigned int height_);

		/**
		* Minimizes window.
		* Uses SDLs internal method to minimize the window.
		*/
		void minimize();

		/**
		* Maximizes window.
		* Uses SDLs internal method to maximize the window.
		*/
		void maximize();

		/**
		* @return The Renderer.
		*/
		Renderer* getRenderer();

	private:
		/**
		* Creates the Window, with specified width and height.
		* Can be used either as the creator, or as the resizer.
		*/
		void create(const unsigned int width_, const unsigned int height_);

		/**
		* Rescales the renderization.
		* Set a device independent resolution for rendering.
		* @param size_ : Multiplies Configuration::resolutionWidth and
		* 	Configuration::resolutionHeight for the new resolution.
		* @note Practically, it looks like the camera has a larger field of view, the bigger
		* 	the size_ parameter is.
		* @see SDL_RenderSetLogicalSize
		*/
		void rescale(unsigned int size_);

		const std::string windowTitle; /**< The game Window title. */
		SDL_Window* sdlWindow; /**< The SDL window, that will be the actual game window. */
		Renderer* renderer; /**< The SDL renderer to render onto. */

};
