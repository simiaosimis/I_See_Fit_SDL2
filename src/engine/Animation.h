#pragma once

#include <SDL2/SDL.h>

/**
* Class in control of animating a sprite.
*
* @todo Control if animation should loop or not.
*/
class Animation {

	public:
		/**
		* @brief The constructor.
		*
		* @param x : The initial x position on the spritesheet.
		* @param y : The initial y position on the spritesheet.
		* @param sprite_width : The width of the sprite to animate (in pixels).
		* @param sprite_height : The height of the sprite to animate (in pixels).
		* @param number_of_images : The number of images to animate inside the spritesheet.
		* @param total_time : The time in seconds each animation loop takes.
		*/
		Animation(const int x, const int y,	const int sprite_width, const int sprite_height,
			const int number_of_images, const double total_time);

		/**
		* @brief The destructor.
		*/
		~Animation();

		/**
		* @brief Updates the animation clip.
		*
		* @param clip : Reference to the clip of whatever object the animation is a part of.
		* @param delta_time : Time elapsed between one frame and the other, independent	of
		*	processing speed.
		*/
		void Update(SDL_Rect& clip, const double delta_time);

		/**
		* @return The current frame the animation is in.
		*/
		int CurrentFrame();

		/**
		* @brief Changes the dimensions of the clip on the spritesheet.
		*
		* @param width : New width of the spritesheet clip;
		* @param height : New height of the spritesheet clip;
		*/
		void SetWidthHeight(const int width, const int height);

		/**
		* @brief Changes the animation to another.
		*
		* @param x : The initial x position on the spritesheet.
		* @param y : The initial y position on the spritesheet.
		* @param number_of_images : The number of images to animate inside the spritesheet.
		* @param total_time : The time in seconds each animation loop takes.
		*/
		void ChangeAnimation(const int x, const int y, const int number_of_images,
			const double total_time);

	private:
		/**
		* @brief Updates the clip to a new position.
		*
		* @param clip : The clip to update.
		* @param x : New x position.
		* @param y : New y position.
		*/
		void UpdateClip(SDL_Rect& clip, const int x, const int y);

		int m_x; /**< The position on x axis on the sprite. */
		int m_y; /**< The position on x axis on the sprite. */
		int m_initial_x; /**< Where to start/restart the animation on x. */
		int m_initial_y; /**< Where to start/restart the animation on y. */
		int m_sprite_width; /**< The sprite width. (in pixels) */
		int m_sprite_height; /**< The sprite height. (in pixels) */
		int m_number_of_images; /**< The number of images to animate inside the	spritesheet. */
		double m_total_elapsed_time; /**< Total time elapsed on the animation, to check if the
			frame changed. */
		double m_total_time; /**< Total time in seconds for each animation loop. */
		int m_animation_count; /**< Index of the current image relative to the number of
			images. */
};
