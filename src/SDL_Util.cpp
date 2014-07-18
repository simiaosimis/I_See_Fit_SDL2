#include "SDL_Util.h"
#include "Logger.h"

void SDL_Wrapper::logSDLVersion(const std::string& what_, const SDL_version& compiled_,
	std::string revision_) {

	Log(DEBUG) << what_ << " Version (Compiled): " << (int)compiled_.major << "." <<
		(int)compiled_.minor << "." << (int)compiled_.patch <<
		((!revision_.empty()) ? revision_ : "");
}
