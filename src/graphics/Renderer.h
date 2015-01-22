#pragma once

#include <SDL2/SDL_image.h>

class Renderer {

	public:
		/**
		* @brief The constructor.
		*
		* @param sdl_window : The SDL_Window object.
		* @param flags : The renderer flags used for initialization (SDL_RendererFlags).
		*/
		Renderer(SDL_Window* const sdl_window, const Uint32 flags);

		/**
		* @brief The destructor.
		*/
		~Renderer();

		/**
		* @brief Clears previous rendering.
		*
		* Initialize the backbuffer for the new frame's drawing.
		*
		* @see SDL_RenderClear
		*/
		void Clear();

		/**
		* @brief Renders everything drawn in a frame.
		*
		* Presents the composed backbuffer to the screen.
		*
		* @see SDL_RenderPresent
		*/
		void Render();

		/**
		* @brief Rescales the renderization.
		*
		* Set a device independent resolution for rendering.
		*
		* @param size : Multiplies Configuration::ResolutionWidth() and
		* 	Configuration::ResolutionHeight() for the new resolution (0+).
		*
		* @note Practically, it looks like the camera has a larger field of view, the bigger
		* 	the size parameter is.
		*
		* @see SDL_RenderSetLogicalSize
		*/
		void SetLogicalSize(const int size);
		
		/**
		* @brief Returns the current set logical size through the parameters.
		*
		* @param width : Current logical width.
		* @param height : Current logical height.
		*/
		void LogicalSize(int* width, int* height);

		/**
		* @return The SDL_Renderer object.
		*/
		SDL_Renderer* SdlRenderer();

	private:
		SDL_Renderer* m_sdl_renderer; /**< The SDL renderer to render onto. */

};
