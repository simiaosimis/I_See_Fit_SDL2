#include "SDL_Util.h"
#include "Logger.h"

void SDL_Wrapper::SDL_Wrapper_detail::logSDLVersion(const std::string& what_,
	const SDL_version& compiled_, std::string revision_) {

	Log(DEBUG) << what_ << " Version (Compiled): " << static_cast<int>(compiled_.major) << "." <<
		static_cast<int>(compiled_.minor) << "." << static_cast<int>(compiled_.patch) <<
		((!revision_.empty()) ? revision_ : "");
}
