#pragma once

#include <SDL2/SDL.h>
#include <string>
#include "util/Logger.h"

namespace sdl {
namespace detail {

/**
* @return Version information about the SDL API.
*
* @param library : What API/Library is being logged about.
* @param version_compiled : The compiled version.
*/
std::string SdlVersion(const std::string& library, const SDL_version& version_compiled);

/**
* @return Version information about the SDL API.
*
* @param library : What API/Library is being logged about.
* @param version_compiled : The compiled version.
* @param revision : The revision version.
*/
std::string SdlVersion(const std::string& library, const SDL_version& version_compiled,
	const std::string& revision);

/**
* @return Information about available video drivers.
*/
std::string SdlVideoDrivers();

/**
* @return Information about available audio drivers.
*/
std::string SdlAudioDrivers();

/**
* @return Information about available render drivers.
*/
std::string SdlRenderDrivers();

/**
* @return Information about available audio devices.
*/
std::string SdlAudioDevices();

/**
* @return Information about all the displays and modes available.
*/
std::string SdlDisplayModes();

/**
* @return A string with the contents of a SDL_RendererInfo.
*/
std::string RendererInfoToString(const SDL_RendererInfo& info);

/**
* @return A string with the compatible audio format.
*/
std::string AudioFormatToString(const Uint16 audio_format);

/**
* @return A string with the compatible pixel format.
*/
std::string PixelFormatToString(const Uint32 texture_format);

/**
* @return A string indicating the supported renderer flags.
*/
std::string RendererFlagsToString(const Uint32 flags);

/**
* @return True is display modes are equal.
*/
bool EqualDisplayModes(const SDL_DisplayMode& first, const SDL_DisplayMode& second);

} // namespace detail
} // namespace sdl
