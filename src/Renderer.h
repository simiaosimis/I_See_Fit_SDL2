#pragma once

#include "SDL_Libs.h"

class Renderer {

	public:
		Renderer(SDL_Window* const sdlWindow_, const Uint32 flags_);
		~Renderer();

		void clear();
		void render();
		void setLogicalSize(unsigned int size_);
		void getLogicalSize(int* w, int* h);
		SDL_Renderer* getSdlRenderer();

	private:
		SDL_Renderer* sdlRenderer; /**< The SDL renderer to render onto. */

};
