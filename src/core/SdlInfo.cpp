#include "core/SdlInfo.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <sstream>
#include "util/Logger.h"

namespace sdl {
namespace detail {

void LogSdlVersion(const std::string& library, const SDL_version& version_compiled) {
	log_debug() << library << " Version (compiled): " <<
		static_cast<int>(version_compiled.major) << "." <<
		static_cast<int>(version_compiled.minor) << "." <<
		static_cast<int>(version_compiled.patch);
}

void LogSdlVersion(const std::string& library, const SDL_version& version_compiled,
		const std::string& revision) {
	log_debug() << library << " Version (compiled): " <<
		static_cast<int>(version_compiled.major) << "." <<
		static_cast<int>(version_compiled.minor) << "." <<
		static_cast<int>(version_compiled.patch) << " " << revision;
}

void LogSdlDrivers(FuncDriverName const func_driver_name,
		FuncNumDrivers const func_num_drivers, LogBuffer& drive_log) {
	///@todo Something for SDL_DisplayMode
	const int k_num_drivers = func_num_drivers();
	if(k_num_drivers >= 1) {
		drive_log << "\n >>> " << k_num_drivers << " drivers compiled into SDL:\n\t";

		for(int i = 0; i < k_num_drivers; i++) {
			drive_log << "(" << (i+1) << ") " << func_driver_name(i) << ", ";
		}
	}
	else {
		log_error() << "Could not get number of drivers. " << SDL_GetError();
	}
}

void LogSdlDrivers(FuncDriverInfo const func_driver_info,
		FuncNumDrivers const func_num_drivers, LogBuffer& drive_log) {
	const int k_num_drivers = func_num_drivers();
	if(k_num_drivers >= 1) {
		drive_log << "\n >>> " << k_num_drivers << " render drivers available:\n";

		SDL_RendererInfo* infos = new SDL_RendererInfo[k_num_drivers];

		for(int i = 0; i < k_num_drivers; i++) {
			const int k_got_info = func_driver_info(i, &infos[i]);
			if(k_got_info == 0){
				drive_log << "\t(" << (i+1) << ") " << RendererInfoToString(infos[i]) << "\n";
			}
			else {
				log_error() << "Could not get renderer info. " << SDL_GetError();
			}
		}

		delete[] infos;
	}
	else {
		log_error() << "Could not get number of drivers. " << SDL_GetError();
	}
}

std::string RendererInfoToString(const SDL_RendererInfo& info) {
	std::ostringstream os;
	os << "[NAME]: " << info.name << ", [FLAGS]: " << info.flags <<
		", [MAX TEXTURE W/H]: " << info.max_texture_width << "/" << info.max_texture_height <<
		", ";

	for(int i = 0; i < static_cast<int>(info.num_texture_formats); i++) {
		os << "[FORMAT-" << (i+1) << "]: " <<
			PixelFormatToString(info.texture_formats[i]) << ", ";
	}

	os << "]";

	return os.str();
}

std::string AudioFormatToString(const Uint16 format) {
	std::string audio_format{"Unidentified!"};

	switch(format) {
        case AUDIO_U8:
        	audio_format = "U8";
        	break;
        case AUDIO_S8:
	        audio_format = "S8";
        	break;
        case AUDIO_U16LSB:
	        audio_format = "U16LSB";
        	break;
        case AUDIO_S16LSB:
	        audio_format = "S16LSB";
        	break;
        case AUDIO_U16MSB:
	        audio_format = "U16MSB";
        	break;
        case AUDIO_S16MSB:
	        audio_format = "S16MSB";
        	break;
        default:
	        log_error() << "Some SDL_Mixer audio format was not listed!";
        	break;
	}

	return audio_format;
}

std::string PixelFormatToString(const Uint32 texture_format) {
	std::string sdl_pixelformat{"Unidentified!"};

	switch(texture_format) {
		case SDL_PIXELFORMAT_UNKNOWN:
			sdl_pixelformat = "UNKNOWN";
			break;
		case SDL_PIXELFORMAT_INDEX1LSB:
			sdl_pixelformat = "INDEX1LSB";
			break;
		case SDL_PIXELFORMAT_INDEX1MSB:
			sdl_pixelformat = "INDEX1MSB";
			break;
		case SDL_PIXELFORMAT_INDEX4LSB:
			sdl_pixelformat = "INDEX4LSB";
			break;
		case SDL_PIXELFORMAT_INDEX4MSB:
			sdl_pixelformat = "INDEX4MSB";
			break;
		case SDL_PIXELFORMAT_INDEX8:
			sdl_pixelformat = "INDEX8";
			break;
		case SDL_PIXELFORMAT_RGB332:
			sdl_pixelformat = "RGB332";
			break;
		case SDL_PIXELFORMAT_RGB444:
			sdl_pixelformat = "RGB444";
			break;
		case SDL_PIXELFORMAT_RGB555:
			sdl_pixelformat = "RGB555";
			break;
		case SDL_PIXELFORMAT_BGR555:
			sdl_pixelformat = "BGR555";
			break;
		case SDL_PIXELFORMAT_ARGB4444:
			sdl_pixelformat = "ARGB4444";
			break;
		case SDL_PIXELFORMAT_RGBA4444:
			sdl_pixelformat = "RGBA4444";
			break;
		case SDL_PIXELFORMAT_ABGR4444:
			sdl_pixelformat = "ABGR4444";
			break;
		case SDL_PIXELFORMAT_BGRA4444:
			sdl_pixelformat = "BGRA4444";
			break;
		case SDL_PIXELFORMAT_ARGB1555:
			sdl_pixelformat = "ARGB1555";
			break;
		case SDL_PIXELFORMAT_RGBA5551:
			sdl_pixelformat = "RGBA5551";
			break;
		case SDL_PIXELFORMAT_ABGR1555:
			sdl_pixelformat = "ABGR1555";
			break;
		case SDL_PIXELFORMAT_BGRA5551:
			sdl_pixelformat = "BGRA5551";
			break;
		case SDL_PIXELFORMAT_RGB565:
			sdl_pixelformat = "RGB565";
			break;
		case SDL_PIXELFORMAT_BGR565:
			sdl_pixelformat = "BGR565";
			break;
		case SDL_PIXELFORMAT_RGB24:
			sdl_pixelformat = "RGB24";
			break;
		case SDL_PIXELFORMAT_RGB888:
			sdl_pixelformat = "RGB888";
			break;
		case SDL_PIXELFORMAT_RGBX8888:
			sdl_pixelformat = "RGBX8888";
			break;
		case SDL_PIXELFORMAT_BGR888:
			sdl_pixelformat = "BGR888";
			break;
		case SDL_PIXELFORMAT_BGRX8888:
			sdl_pixelformat = "BGRX8888";
			break;
		case SDL_PIXELFORMAT_ARGB8888:
			sdl_pixelformat = "ARGB8888";
			break;
		case SDL_PIXELFORMAT_RGBA8888:
			sdl_pixelformat = "RGBA8888";
			break;
		case SDL_PIXELFORMAT_ABGR8888:
			sdl_pixelformat = "ABGR8888";
			break;
		case SDL_PIXELFORMAT_BGRA8888:
			sdl_pixelformat = "BGRA8888";
			break;
		case SDL_PIXELFORMAT_ARGB2101010:
			sdl_pixelformat = "ARGB2101010";
			break;
		case SDL_PIXELFORMAT_YV12:
			sdl_pixelformat = "YV12";
			break;
		case SDL_PIXELFORMAT_IYUV:
			sdl_pixelformat = "IYUV";
			break;
		case SDL_PIXELFORMAT_YUY2:
			sdl_pixelformat = "YUY2";
			break;
		case SDL_PIXELFORMAT_UYVY:
			sdl_pixelformat = "UYVY";
			break;
		case SDL_PIXELFORMAT_YVYU:
			sdl_pixelformat = "YVYU";
			break;
		default:
			log_error() << "Some SDL_PIXELFORMAT was not listed!";
			break;
	}

	return sdl_pixelformat;
}

} // namespace detail
} // namespace sdl
