#pragma once

#include <SDL2/SDL.h>
#include "engine/GameObject.h"

namespace sdl2engine {

/**
* Simple collision detection.
*/
class Collision {

	public:
		/**
		* Possible sides a rectangle can collide.
		*/
		enum RectangleSide : uint8_t {
			TOP = 0,
			BOTTOM,
			LEFT,
			RIGHT,
			NONE
		};

		/**
		* @return Whether two SDL_Rects collided.
		* @param a_ , b_ : The rectangles to check.
		*/
		static bool rectsCollided(const SDL_Rect& a_, const SDL_Rect& b_);

		/**
		* @return The side (RectangleSide) which two SDL_Rects collided on.
		* @param a_ , b_ : The rectangles to check.
		*/
		static RectangleSide rectsCollidedSide(const SDL_Rect& a_, const SDL_Rect& b_);
};

} // namespace sdl2engine
