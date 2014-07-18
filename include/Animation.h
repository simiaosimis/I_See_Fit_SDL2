#pragma once

#include "SDL_Libs.h"

/**
* Class in control of animating a sprite.
* @todo Control if animation should loop or not.
*/
class Animation {

	public:
		/**
		* The constructor.
		* @param x_ : The initial x position on the spritesheet.
		* @param y_ : The initial y position on the spritesheet.
		* @param spriteWidth_ : The width of the sprite to animate (in pixels).
		* @param spriteHeight_ : The height of the sprite to animate (in pixels).
		* @param numberOfImages_ : The number of images to animate inside the spritesheet.
		* @param totalTime_ : The time in seconds each animation loop takes.
		*/
		Animation(const unsigned int x_, const unsigned int y_,
			const unsigned int spriteWidth_, const unsigned int spriteHeight_,
			const unsigned int numberOfImages_, const double totalTime_);

		/**
		* The destructor.
		*/
		~Animation();

		/**
		* Updates the animation clip.
		* @param clip_ : Reference to the clip of whatever object the animation is a part of.
		* @param dt_ : Delta time. Time elapsed between one frame and the other, independent
		* 	of processing speed.
		*/
		void update(SDL_Rect& clip_, const double dt_);

		/**
		* @return The current frame the animation is in.
		*/
		unsigned int getCurrentFrame();

		/**
		* Changes the dimensions of the clip on the spritesheet.
		*/
		void changeWidthHeight(const unsigned int width_, const unsigned int height_);

		/**
		* Changes the animation to another.
		* @note See Animation::Animation for the parameters descriptions.
		*/
		void changeAnimation(const unsigned int x_, const unsigned int y_,
			const unsigned int numberOfImages_,	const double totalTime_);

	private:
		/**
		* Updates the clip to a new position.
		* @param clip_ : The clip to update.
		* @param x_ : New x position.
		* @param y_ : New y position.
		*/
		void updateClip(SDL_Rect& clip_, const unsigned int x_, const unsigned int y_);

		unsigned int x; /**< The position on x axis on the sprite. */
		unsigned int y; /**< The position on x axis on the sprite. */
		unsigned int initialX; /**< Where to start/restart the animation on x. */
		unsigned int initialY; /**< Where to start/restart the animation on y. */
		unsigned int spriteWidth; /**< The sprite width. (in pixels) */
		unsigned int spriteHeight; /**< The sprite height. (in pixels) */
		unsigned int numberOfImages; /**< The number of images to animate inside the
			spritesheet. */
		double totalElapsedTime; /**< Total time elapsed on the animation, to check if the
			frame changed. */
		double totalTime; /**< Total time in seconds for each animation loop. */
		unsigned int animationCount; /**< Index of the current image relative to the number of
			images. */

};
