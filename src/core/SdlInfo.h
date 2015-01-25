#pragma once

#include <SDL2/SDL.h>
#include <string>
#include "util/Logger.h"

namespace sdl {
namespace detail {

using FuncDriverName = const char* (*) (int);
using FuncNumDrivers = int (*) ();
using FuncDriverInfo = int (*) (int, SDL_RendererInfo*);

/**
* Logs the SDL API version.
* @param library : What API/Library is being logged about.
* @param version_compiled : The compiled version.
* @param revision : If any, the revision.
*/
void LogSdlVersion(const std::string& library, const SDL_version& version_compiled);

/**
* Logs the SDL API version.
* @param library : What API/Library is being logged about.
* @param version_compiled : The compiled version.
* @param revision : If any, the revision.
*/
void LogSdlVersion(const std::string& library, const SDL_version& version_compiled,
	const std::string& revision);

/**
* @brief Logs information about available drivers.
*
* Ment for Audio and Video drivers.
*/
void LogSdlDrivers(FuncDriverName const func_driver_name,
	FuncNumDrivers const func_num_drivers, LogBuffer& drive_log);

/**
* @brief Logs information about available drivers.
*
* Ment for Render drivers.
*/
void LogSdlDrivers(FuncDriverInfo const func_driver_info,
	FuncNumDrivers const func_num_drivers, LogBuffer& drive_log);

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

} // namespace detail
} // namespace sdl
