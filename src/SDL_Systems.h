#pragma once

/**
* Wraps the SDL libraries.
* And contains the initializing and closing functions for the system(s). No instances
	necessary.
*/
namespace sdl {

/**
* The system initializer.
* Initializes all the SDL systems and/or subsystems.
* @return True if every system was initialized successfully, else it returns false.
*/
bool Initialize();

/**
* Closes all open systems.
* Closes all systems and/or subsystems opened by the initializer method.
* @see Initialize()
*/
void Close();

} // namespace sdl
