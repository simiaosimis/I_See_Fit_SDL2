#include "util/Configuration.h"
#include "util/Assert.h"

namespace sdl2engine {

// Resolution = 16:10
const int Configuration::m_resolution_width = 192;
const int Configuration::m_resolution_height = 108;
Uint32 Configuration::m_max_framerate = 0;
const char* Configuration::m_window_title = "";
int Configuration::m_logical_render_size = 0;
int Configuration::m_screen_width = 0;
int Configuration::m_screen_height = 0;
int Configuration::m_camera_distance_width = 0;
int Configuration::m_camera_distance_height = 0;

void Configuration::Initialize() {
	/// @todo Read this information from a configuration file.
	Configuration::m_max_framerate = 60;
	Configuration::m_window_title = "sdl2-engine";
	Configuration::m_logical_render_size = 8;
	Configuration::m_camera_distance_width =
		Configuration::m_resolution_width * Configuration::m_logical_render_size;
	Configuration::m_camera_distance_height =
		Configuration::m_resolution_height * Configuration::m_logical_render_size;
	Configuration::m_screen_width = 1920 / 2;
	Configuration::m_screen_height = 1080 / 2;

	ASSERT(Configuration::m_resolution_width >= 0	   , "Must be >= 0");
	ASSERT(Configuration::m_resolution_height >= 0	   , "Must be >= 0");
	ASSERT(Configuration::m_logical_render_size >= 0   , "Must be >= 0");
	ASSERT(Configuration::m_screen_width >= 0		   , "Must be >= 0");
	ASSERT(Configuration::m_screen_height >= 0		   , "Must be >= 0");
	ASSERT(Configuration::m_camera_distance_width >= 0 , "Must be >= 0");
	ASSERT(Configuration::m_camera_distance_height >= 0, "Must be >= 0");
}

int Configuration::ResolutionWidth() {
	return Configuration::m_resolution_width;
}

int Configuration::ResolutionHeight() {
	return Configuration::m_resolution_height;
}

Uint32 Configuration::MaxFramerate() {
	return Configuration::m_max_framerate;
}

const char* Configuration::WindowTitle() {
	return Configuration::m_window_title;
}

int Configuration::LogicalRenderSize() {
	return Configuration::m_logical_render_size;
}

int Configuration::ScreenWidth() {
	return Configuration::m_screen_width;
}

int Configuration::ScreenHeight() {
	return Configuration::m_screen_height;
}

int Configuration::CameraDistanceWidth() {
	return Configuration::m_camera_distance_width;
}

int Configuration::CameraDistanceHeight() {
	return Configuration::m_camera_distance_height;
}

} // namespace sdl2engine
