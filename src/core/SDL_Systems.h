#pragma once

/**
* @brief Encloses initialization/closing of SDL systems.
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
