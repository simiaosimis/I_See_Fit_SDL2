#include "core/SdlSystems.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <cstdlib>
#include <string>
#include "core/SdlInfo.h"
#include "util/Logger.h"

namespace {

/**
* @brief Initializes SDL_TTF systems.
*/
bool OpenSdlTtf() {
	bool success = false;
	const int k_ttf_init = TTF_Init();
	if(k_ttf_init == 0) {
		success = true;

		SDL_version compiled;
		SDL_TTF_VERSION(&compiled);
		sdl::detail::LogSdlVersion("SDL_TTF", compiled);
	}
	else {
		log_error() << "Could not initialize TTF. " << TTF_GetError();
	}

	const int k_registered_atexit = std::atexit(TTF_Quit);
	if(k_registered_atexit != 0){
		log_error() << "Failed to register TTF_Quit to exit.";
	}

	const int k_registered_at_quick_exit = std::at_quick_exit(TTF_Quit);
	if(k_registered_at_quick_exit != 0){
		log_error() << "Failed to register TTF_Quit to quick_exit.";
	}

	return success;
}

/**
* @brief Initializes SDL systems.
*/
bool OpenSdl() {
	bool success = false;

	const Uint32 k_init_flags = SDL_INIT_EVERYTHING;
	const int sdl_init = SDL_Init(k_init_flags);
	if(sdl_init == 0) {
		success = true;

		SDL_version compiled;
		SDL_GetVersion(&compiled);

		sdl::detail::LogSdlVersion("SDL", compiled, SDL_GetRevision());
	}
	else {
		log_error() << "Could not initialize SDL. " << SDL_GetError();
	}

	const int k_registered_atexit = std::atexit(SDL_Quit);
	if(k_registered_atexit != 0){
		log_error() << "Failed to register SDL_Quit to exit.";
	}

	const int k_registered_at_quick_exit = std::at_quick_exit(SDL_Quit);
	if(k_registered_at_quick_exit != 0){
		log_error() << "Failed to register SDL_Quit to quick_exit.";
	}

	return success;
}

/**
* @brief Initializes SDL_Image systems.
*/
bool OpenSdlImage() {
	const Uint32 k_img_flags = IMG_INIT_PNG;
	bool success = (static_cast<Uint32>(IMG_Init(k_img_flags)) & k_img_flags);
	if(success) {
		SDL_version compiled;
		SDL_IMAGE_VERSION(&compiled);
		sdl::detail::LogSdlVersion("SDL_image", compiled);
	}
	else {
		log_error() << "Could not initialize SDL_Image. " << IMG_GetError();
	}

	const int k_registered_atexit = std::atexit(IMG_Quit);
	if(k_registered_atexit != 0){
		log_error() << "Failed to register IMG_Quit to exit.";
	}

	const int k_registered_at_quick_exit = std::at_quick_exit(IMG_Quit);
	if(k_registered_at_quick_exit != 0){
		log_error() << "Failed to register IMG_Quit to quick_exit.";
	}

	return success;
}

/**
* @brief Properly closes SDL_Mixer.
*
* Also logs a small about of debug info about the audio.
*/
void CloseMixer() {
	// Query the specifications of the opened audio, to figure out how many times we need to
	// close the audio.
	int frequency = 0;
	int channels = 0;
	Uint16 format = 0;
	const int k_numbers_of_times_opened = Mix_QuerySpec(&frequency, &format, &channels);
	int times_to_close = k_numbers_of_times_opened;

	if(k_numbers_of_times_opened != 0) {
		log_debug() << "Audio opened " << k_numbers_of_times_opened << " time(s). Frequency: "
			<< frequency << "Hz. Format: " << sdl::detail::AudioFormatToString(format) <<
			". Channels: " << channels << " " << ((channels == 2) ? "(stereo)" : "(mono)") <<
			".";
	}
	else {
		log_error() << "Error querying the specifications of the audio. " << Mix_GetError();

		// Set the amount of times to close the audio to one, just for safety.
		times_to_close = 1;
	}

	// Close the audio the necessary amount of times.
	while(times_to_close > 0){
		Mix_CloseAudio();
		times_to_close--;
	}

	// "Since each call to Mix_Init may set different flags, there is no way, currently, to
	// request how many times each one was initted. In other words, the only way to quit for
	// sure is to do a loop like so: "
	while(Mix_Init(0)){
		Mix_Quit();
	}
}

/**
* @brief Initializes SDL_Mixer systems.
*/
bool OpenSdlMixer() {
	bool success = false;

	const int k_frequency = 44100;
	const int k_channels = 2;
	const int k_chunk_size = 4096;

	const int k_initialized_audio = Mix_OpenAudio(k_frequency, MIX_DEFAULT_FORMAT, k_channels,
		k_chunk_size);
	if(k_initialized_audio == 0) {
		success = true;

		SDL_version compiled;
		SDL_MIXER_VERSION(&compiled);
		sdl::detail::LogSdlVersion("SDL_mixer", compiled);

		const int k_channels_to_allocate = 25;
		const int k_channels_allocated = Mix_AllocateChannels(k_channels_to_allocate);

		log_debug() << "Allocated " << k_channels_allocated << " out of "
			<< k_channels_to_allocate << " requested channels for SDL_Mixer.";
	}
	else {
		log_error() << "Could not initialize SDL_Mixer. " << Mix_GetError();
	}

	const int k_registered_atexit = std::atexit(CloseMixer);
	if(k_registered_atexit != 0){
		log_error() << "Failed to register CloseMixer to exit.";
	}

	const int k_registered_at_quick_exit = std::at_quick_exit(CloseMixer);
	if(k_registered_at_quick_exit != 0){
		log_error() << "Failed to register CloseMixer to quick_exit.";
	}

	return success;
}

} // namespace

namespace sdl {

bool Initialize() {
	log_debug() << "Initializing systems...";

	const bool success_ttf = OpenSdlTtf();
	const bool success_sdl = OpenSdl();
	const bool success_img = OpenSdlImage();
	const bool success_mixer = OpenSdlMixer();

	// Getting some driver information.
	{
		LogBuffer driver_log{log_debug()};
		driver_log << "Getting driver information.";
		detail::LogSdlDrivers(SDL_GetVideoDriver, SDL_GetNumVideoDrivers, driver_log);
		detail::LogSdlDrivers(SDL_GetAudioDriver, SDL_GetNumAudioDrivers, driver_log);
		detail::LogSdlDrivers(SDL_GetRenderDriverInfo, SDL_GetNumRenderDrivers, driver_log);
	}

	// If even one system fails to initialize, returns false.
	return (success_sdl && success_img && success_mixer && success_ttf);
}

} // namespace sdl
