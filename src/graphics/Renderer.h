#pragma once

#include <SDL2/SDL_image.h>

class Renderer {

	public:
		Renderer(SDL_Window* const sdlWindow_, const Uint32 flags_);
		~Renderer();

		void clear();
		void render();

		/**
		* Rescales the renderization.
		* Set a device independent resolution for rendering.
		* @param size_ : Multiplies Configuration::ResolutionWidth() and
		* 	Configuration::ResolutionHeight() for the new resolution (0+).
		* @note Practically, it looks like the camera has a larger field of view, the bigger
		* 	the size_ parameter is.
		* @see SDL_RenderSetLogicalSize
		*/
		void setLogicalSize(int size_);
		
		void getLogicalSize(int* w, int* h);
		SDL_Renderer* getSdlRenderer();

	private:
		SDL_Renderer* sdlRenderer; /**< The SDL renderer to render onto. */

};
