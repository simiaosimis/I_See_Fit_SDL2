#pragma once

#include <string>

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
		static uint32_t MaxFramerate();

		/**
		* @return m_window_title
		*/
		static std::string WindowTitle();

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

		static uint32_t m_max_framerate; /**< The game's max framerate. */
		static std::string m_window_title; /**< The game window's title. */

		static int m_logical_render_size; /**< The size of the logical rendering. */

		static int m_screen_width; /**< The screen width. */
		static int m_screen_height; /**< The screen height. */

		static int m_camera_distance_width; /**< The width distance of the camera. */
		static int m_camera_distance_height; /**< The height distance of the camera. */

};
