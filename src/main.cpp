#include "Game.h"
#include "Logger.h"
#include "Configuration.h"
#include "SDL_Systems.h"
#include "UsefulDefines.h"

int main(int argc, char** argv) {

	// Unused.
	UNUSED(argc);
	UNUSED(argv);

	Log(DEBUG) << "Starting sdl2-engine...";

	Configuration::initialize();

	const bool systemsInitialized = SDL_Wrapper::initialize();

	if(systemsInitialized) {
		Game::instance().runGame();
		delete &Game::instance();
	}
	else {
		Log(ERROR) << "Systems were not initialized.";
	}

	SDL_Wrapper::close();

	Log(DEBUG) << "Exiting sdl2-engine...";
	return 0;
}
