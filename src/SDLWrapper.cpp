#include "SDLWrapper.h"
#include "SDLUtil.h"
#include "Logger.h"

bool SDLWrapper::initialize() {
	bool successSDL = false;
	bool successIMG = false;
	bool successMixer = false;
	bool successTTF = false;

	SDL_version compiled;

	Log(DEBUG) << "Initializing systems...";

	// Initializing SDL_TTF.
	const int ttfInit = TTF_Init();
	if(ttfInit == 0) {
		successTTF = true;

		SDL_TTF_VERSION(&compiled);
		SDLWrapper::logSDLVersion("SDL_TTF", compiled);
	}
	else {
		Log(ERROR) << "Could not initialize TTF." << TTF_GetError();
	}

	// Initializing SDL with initFlags.
	const Uint32 initFlags = SDL_INIT_EVERYTHING;
	const int sdlInit = SDL_Init(initFlags);

	if(sdlInit == 0) {
		successSDL = true;

		SDL_version linked;
		SDL_VERSION(&compiled);
		SDL_GetVersion(&linked);

		SDLWrapper::logSDLVersion("SDL", compiled, SDL_GetRevision());
	}
	else {
		Log(ERROR) << "Could not initialize SDL." << SDL_GetError();
	}

	// Initializing SDL_image with imgFlags.
	const Uint32 imgFlags = IMG_INIT_PNG;
	if((IMG_Init(imgFlags) & imgFlags)) {
		successIMG = true;

		SDL_IMAGE_VERSION(&compiled);
		SDLWrapper::logSDLVersion("SDL_image", compiled);
	}
	else {
		Log(ERROR) << "Could not initialize SDL_Image." << IMG_GetError();
	}

	// Initializing SDL_mixer.
	const int frequency = 44100;
	const int channels = 2;
	const int chunksize = 4096;
	const int initialized = Mix_OpenAudio(frequency, MIX_DEFAULT_FORMAT, channels, chunksize);
	if(initialized == 0) {
		successMixer = true;

		SDL_MIXER_VERSION(&compiled);
		SDLWrapper::logSDLVersion("SDL_mixer", compiled);

		const int channelsAllocated = Mix_AllocateChannels(25);

		Log(DEBUG) << "Allocated " << channelsAllocated << " channels for the mixer.";
	}
	else {
		Log(ERROR) << "Could not initialize SDL_Mixer" << Mix_GetError();
	}

	// If even one system fails to initialize, returns false.
	return (successSDL && successIMG && successMixer && successTTF);
}

void SDLWrapper::close() {
	Log(DEBUG) << "Closing SDL.";

	// Quits SDL_mixer.
	SDLWrapper_detail::closeMixer();

	// Quits SDL_image.
	IMG_Quit();

	// Quits SDL.
	SDL_Quit();

	// Quits SDL_TTF.
	TTF_Quit();
}

void SDLWrapper::SDLWrapper_detail::closeMixer() {
	// Query the specifications of the opened audio, to figure out how many times we need to
	// close the audio.
	int frequency = 0;
	int channels = 0;
	Uint16 format = 0;
	const int numberOfTimesOpened = Mix_QuerySpec(&frequency, &format, &channels);
	int timesToClose = numberOfTimesOpened;

	if(numberOfTimesOpened != 0) {
		// Build a string with the format.
		std::string format_str("Unknown format");
	    switch(format) {
	        case AUDIO_U8:
	        	format_str="U8";
	        	break;
	        case AUDIO_S8:
		        format_str="S8";
	        	break;
	        case AUDIO_U16LSB:
		        format_str="U16LSB";
	        	break;
	        case AUDIO_S16LSB:
		        format_str="S16LSB";
	        	break;
	        case AUDIO_U16MSB:
		        format_str="U16MSB";
	        	break;
	        case AUDIO_S16MSB:
		        format_str="S16MSB";
	        	break;
	        default:
	        	break;
	    }

	    // Build a string with the channels type.
	    std::string channels_str("Unknown channels");
	    switch(channels) {
	    	case 1:
	    		channels_str = "(mono)";
	    		break;
	    	case 2:
	    		channels_str = "(stereo)";
	    		break;
	    	default:
	    		break;
	    }

		Log(DEBUG) << "Audio opened " << numberOfTimesOpened << " time(s). Frequency: " <<
			frequency << "Hz. Format: " << format_str << ". Channels: " << channels << " " <<
			channels_str << ".";
	}
	else {
		Log(ERROR) << "Error querying the specifications of the audio. " << Mix_GetError();

		// Set the amount of times to close the audio to one, just for safety.
		timesToClose = 1;
	}

	// Close the audio the necessary amount of times.
	while(timesToClose > 0){
		Mix_CloseAudio();
		timesToClose--;
	}

	// "Since each call to Mix_Init may set different flags, there is no way, currently, to
	// request how many times each one was initted. In other words, the only way to quit for
	// sure is to do a loop like so: "
	while(Mix_Init(0)){
		Mix_Quit();
	}
}
