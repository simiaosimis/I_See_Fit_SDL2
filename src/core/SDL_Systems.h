#pragma once

/**
* @brief Wraps the SDL libraries.
*
* And contains the initializing and closing functions for the system(s). No instances
*	necessary.
*/
namespace sdl {

/**
* @brief The system initializer.
*
* Initializes all the SDL systems and/or subsystems.
*
* @return True if every system was initialized successfully.
*/
bool Initialize();

/**
* @brief Closes all open systems.
*
* Closes all systems and/or subsystems opened by the initializer method.
*
* @see Initialize()
*/
void Close();

} // namespace sdl
