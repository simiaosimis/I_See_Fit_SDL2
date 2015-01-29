#pragma once

#include <SDL2/SDL_ttf.h>
#include "engine/GameObject.h"

namespace sdl2engine {

/**
* @todo Actually make this work.
*/
class Text : public GameObject {

	public:
		Text(const double x_, const double y_, const char* path_, const int size_,
			const char* text_, const SDL_Color color_);

		Text(const double x_, const double y_, const char* path_, const int size_,
			const char* text_);

		virtual ~Text();

		/**
		* Updates the text.
		* @param dt_ : Delta time. Time elapsed between one frame and the other.
		*/
		virtual void update(const double dt_);

		/**
		* Renders the text.
		* @param cameraX_ : The x position of the camera.
		* @param cameraY_ : The y position of the camera.
		*/
		virtual void render(const double cameraX_, const double cameraY_);

		virtual void changeText(const char* text_, const SDL_Color color_);
		virtual void changeText(const char* text_);

	private:
		TTF_Font* font;
};

} // namespace sdl2engine
