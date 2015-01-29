#pragma once

namespace sdl2engine {
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

} // namespace sdl
} // namespace sdl2engine
