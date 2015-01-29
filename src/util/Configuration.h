#pragma once

#include <SDL2/SDL_stdinc.h>

namespace sdl2engine {

/**
*/
class Configuration {

	public:
		/**
		* Initializes all the attributes.
		*/
		static void Initialize();

		/**
		* @return m_resolution_width
		*/
		static int ResolutionWidth();

		/**
		* @return m_resolution_height
		*/
		static int ResolutionHeight();

		/**
		* @return m_max_framerate
		*/
		static Uint32 MaxFramerate();

		/**
		* @return m_window_title
		*/
		static const char* WindowTitle();

		/**
		* @return initialMultiplier
		* @see Window::rescale
		*/
		static int LogicalRenderSize();

		/**
		* @return m_camera_distance_width
		*/
		static int CameraDistanceWidth();

		/**
		* @return m_camera_distance_height
		*/
		static int CameraDistanceHeight();

		/**
		* @return The current screen width.
		*/
		static int ScreenWidth();

		/**
		* @return The current screen height.
		*/
		static int ScreenHeight();

	private:
		static const int m_resolution_width; /**< The game's width resolution. (16) */
		static const int m_resolution_height; /**< The game's height resolution. (10) */

		static Uint32 m_max_framerate; /**< The game's max framerate. */
		static const char* m_window_title; /**< The game window's title. */

		static int m_logical_render_size; /**< The size of the logical rendering. */

		static int m_screen_width; /**< The screen width. */
		static int m_screen_height; /**< The screen height. */

		static int m_camera_distance_width; /**< The width distance of the camera. */
		static int m_camera_distance_height; /**< The height distance of the camera. */
};

} // namespace sdl2engine
