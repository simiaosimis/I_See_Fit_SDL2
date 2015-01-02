#pragma once

/**
* Wraps the SDL libraries.
* And contains the initializing and closing functions for the system(s). No instances
	necessary.
*/
namespace SDL_Wrapper {

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
	namespace SDL_Wrapper_detail {
		/**
		* Properly close the SDL_Mixer library.
		*/
		void closeMixer();
	}

}
