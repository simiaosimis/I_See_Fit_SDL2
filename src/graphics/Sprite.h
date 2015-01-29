#pragma once

#include <SDL2/SDL_image.h>
#include <string>

namespace sdl2engine {

/**
* @brief Visual representation of game objects.
*
* Holds the SDL_Texture from the SDL2 library.
*/
class Sprite {

	public:
		/**
		* @brief The regular constructor.
		*
		* Initializes all the data, and sets the desired renderer. Loads image with the desired
		* 	path.
		*
		* @param path : the image path.
		* @see Sprite::LoadFrom
		*/
		explicit Sprite(const std::string& path);

		/**
		* @brief The constructor from a surface.
		*
		* Created to help the Text class.
		*
		* @param surface : The SDL_Surface from which to construct the sprite.
		*/
		explicit Sprite(SDL_Surface* const surface);

		/**
		* @brief The destructor.
		*/
		~Sprite();

		/**
		* @brief Renders the sprite.
		*
		* Copy the SDL_Texture onto the renderer, at the desired x,y position.
		*
		* @param x : The position on the x axis of the screen.
		* @param y : The position on the y axis of the screen.
		* @param clip : Clips the texture, on the SDL_Rect bounds. If omitted, renders entire
		* 	texture.
		* @param stretch : Whether to stretch the image to the entire screen or not.
		* @param angle : An angle in degrees that indicates the rotation that will be applied
		* 	to the renderQuad. If omitted, no rotation will be applied.
		* @param center : A point indicating the point around which renderQuad will be
		* 	rotated. If omitted, rotation will be done in width/height center.
		* @param flip : Value static which flipping actions should be performed on the
		* 	texture.
		*
		* @note The only obligatory parameters are x and y.
		* @note If the Window renderer is null, will halt the game.
		* @note If it fails to render, logs an error message.
		*/
		void Render(const double x, const double y, SDL_Rect* const clip = nullptr,
			const bool stretch = false, const double angle = 0.0,
			SDL_Point* const center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

		/**
		* @return The Sprite width.
		*/
		int Width();

		/**
		* @brief Set the width.
		*/
		void SetWidth(int width);

		/**
		* @brief Set the height.
		*/
		void SetHeight(int height);

		/**
		* @return The Sprite height.
		*/
		int Height();

		/**
		* @return The path to the image composing the texture.
		*/
		std::string Path();

		/**
		* @return The alpha value of the Sprite.
		*/
		double Alpha();

		/**
		* @brief Set the alpha value.
		*/
		void SetAlpha(int alpha);

	private:
		/**
		* @brief Loads image from a path.
		*
		* Given an existing path for an image, loads the SDL_Texture from it.
		*
		* @param path : the image path.
		*
		* @note Error message is logged if the sprite's SDL_Texture (m_sdl_texture) is null
		*	after this method.
		*/
		void LoadFrom(const std::string& path);

		/**
		* @brief Converts a SDL_Surface to a SDL_Texture.
		*/
		SDL_Texture* SurfaceToTexture(SDL_Surface* const surface);

		/**
		* @brief Sets the blend mode of the Sprite.
		*/
		void SetBlendMode(SDL_BlendMode blend_mode);

		SDL_Texture* m_sdl_texture; /**< The SDL texture to use as the image. */
		int m_width; /**< The loaded image's width. */
		int m_height; /**< The loaded image's width. */
		const std::string m_path; /**< Holds the path from where the Sprite was loaded. */
};

} // namespace sdl2engine
