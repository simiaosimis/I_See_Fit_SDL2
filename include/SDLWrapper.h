#pragma once

// Add other SDL libraries here.
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL2_framerate.h>

/**
* Wraps the SDL libraries.
* And contains the initializing and closing functions for the system(s). No instances
	necessary.
*/
namespace SDLWrapper {

	/**
	* The system initializer.
	* Initializes all the SDL systems and/or subsystems.
	* @return True if every system was initialized successfully, else it returns false.
	*/
	bool initialize();

	/**
	* Closes all open systems.
	* Closes all systems and/or subsystems opened by the initializer method.
	* @see initialize()
	*/
	void close();

	/**
	* Further encapsulating some functions that clients should not use.
	*/
	namespace SDLWrapper_detail {
		/**
		* Properly close the SDL_Mixer library.
		*/
		void closeMixer();
	}

}
