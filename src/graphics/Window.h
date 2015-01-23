#pragma once

#include <SDL2/SDL_image.h>
#include <string>
#include "graphics/Renderer.h"

/**
* Represents the actual window that the game runs on.
* Contains the SDL_Window and the SDL_Renderer, and methods related to these.
*/
class Window {

	public:
		/**
		* @brief The constructor.
		*
		* @see Window::create
		*/
		Window();

		/**
		* @brief The destructor.
		*/
		~Window();

		/**
		* Resizes the window.
		*
		* @param width_ : The desired window width (0+).
		* @param height_ : The desired window height (0+).
		*
		* @todo Instead of directly choosing width and height, choose from a pre-defined list
		* 	of resolutions.
		*/
		void Resize(const int width_, const int height_);

		/**
		* @brief Minimizes window.
		*
		* @see SDL_MinimizeWindow
		*/
		void Minimize();

		/**
		* @brief Maximizes window.
		* 
		* @see SDL_MaximizeWindow
		*/
		void Maximize();

		/**
		* @return The Renderer pointer.
		*
		* @note The 'Get' was added to the name to avoid conflict with class Renderer.
		*/
		Renderer* GetRenderer();

	private:
		/**
		* @brief Creates the Window.
		*
		* Can be used either as the creator, or as the resizer. Gets the size from
		*	Configuration.
		*/
		void Create();

		SDL_Window* m_sdl_window; /**< The SDL window, that will be the actual game window. */
		Renderer* m_renderer; /**< The SDL renderer to render onto. */

};
