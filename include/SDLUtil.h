#pragma once

#include "SDLWrapper.h"
#include <string>

namespace SDLWrapper {

	/**
	* Logs the SDL API version.
	* @param what_ : What API is being logged about.
	* @param compiled_ : The compiled version.
	* @param linked_ : The linked version.
	* @param revision_ : If any, the revision.
	*/
	void logSDLVersion(const std::string& what_, const SDL_version& compiled_,
		std::string revision_ = std::string(""));

}
