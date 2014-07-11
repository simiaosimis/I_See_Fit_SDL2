#include "Game.h"
#include "Logger.h"
#include "Configuration.h"
#include "UsefulDefines.h"

int main(int argc, char** argv){

	// Unused.
	UNUSED(argc);
	UNUSED(argv);

	Log(DEBUG) << "Starting sdl2-engine...";

	Configuration::initialize();

	const bool systemsInitialized = SDLWrapper::initialize();

	if(systemsInitialized){
		Game::instance().runGame();
		delete &Game::instance();
	}
	else{
		Log(ERROR) << "Systems were not initialized.";
	}

	SDLWrapper::close();

	Log(DEBUG) << "Exiting sdl2-engine...";
	return 0;
}
