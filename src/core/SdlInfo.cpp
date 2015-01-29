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

std::string SdlVersion(const std::string& library, const SDL_version& version_compiled) {
	std::ostringstream oss;
	oss << library << " Version (compiled): " << static_cast<int>(version_compiled.major) <<
		"." << static_cast<int>(version_compiled.minor) << "." <<
		static_cast<int>(version_compiled.patch);
	return oss.str();
}

std::string SdlVersion(const std::string& library, const SDL_version& version_compiled,
		const std::string& revision) {
	std::ostringstream oss;
	oss << library << " Version (compiled): " << static_cast<int>(version_compiled.major) <<
		"." << static_cast<int>(version_compiled.minor) << "." <<
		static_cast<int>(version_compiled.patch) << " " << revision;
	return oss.str();
}

std::string SdlVideoDrivers() {
	std::ostringstream oss;

	const std::string current_video_driver{SDL_GetCurrentVideoDriver()};

	const int k_num_video_drivers = SDL_GetNumVideoDrivers();
	if(k_num_video_drivers >= 1) {
		oss << k_num_video_drivers << " video driver(s) compiled into SDL:";

		for(int i = 0; i < k_num_video_drivers; i++) {
			const std::string video_driver{SDL_GetVideoDriver(i)};
			oss << "\n\t(" << (i+1) << ") " << video_driver;

			if(current_video_driver == video_driver) {
				oss << " [* CURRENT]";
			}
		}
	}
	else {
		log_error() << "Could not get number of video drivers. " << SDL_GetError();
	}

	return oss.str();
}

std::string SdlAudioDrivers() {
	std::ostringstream oss;

	const std::string current_audio_driver{SDL_GetCurrentAudioDriver()};

	const int k_num_audio_drivers = SDL_GetNumAudioDrivers();
	if(k_num_audio_drivers >= 1) {
		oss << k_num_audio_drivers << " audio driver(s) compiled into SDL:";

		for(int i = 0; i < k_num_audio_drivers; i++) {
			const std::string audio_driver{SDL_GetAudioDriver(i)};
			oss << "\n\t(" << (i+1) << ") " << audio_driver;

			if(current_audio_driver == audio_driver) {
				oss << " [* CURRENT]";
			}
		}
	}
	else {
		log_error() << "Could not get number of audio drivers. " << SDL_GetError();
	}

	return oss.str();
}

std::string SdlRenderDrivers() {
	std::ostringstream oss;

	const int k_num_render_drivers = SDL_GetNumRenderDrivers();
	if(k_num_render_drivers >= 1) {
		oss << k_num_render_drivers << " render driver(s) available:";

		SDL_RendererInfo* infos = new SDL_RendererInfo[k_num_render_drivers];

		for(int i = 0; i < k_num_render_drivers; i++) {
			const int k_got_info = SDL_GetRenderDriverInfo(i, &infos[i]);
			if(k_got_info == 0){
				oss << "\n\t(" << (i+1) << ") " << RendererInfoToString(infos[i]);
			}
			else {
				log_error() << "Could not get renderer info. " << SDL_GetError();
			}
		}

		delete[] infos;
	}
	else {
		log_error() << "Could not get number of render drivers. " << SDL_GetError();
	}

	return oss.str();
}

std::string SdlAudioDevices() {
	std::ostringstream oss;

	const int k_num_audio_devices = SDL_GetNumAudioDevices(0);
	if(k_num_audio_devices >= 1) {
		oss << k_num_audio_devices << " audio device(s) available:";

		for(int i = 0; i < k_num_audio_devices; i++) {
			const char* audio_device_name = SDL_GetAudioDeviceName(i, 0);
			if(audio_device_name != nullptr) {
				oss << "\n\t(" << (i+1) << ") " << audio_device_name;
			}
			else{
				log_error() << "Could not get audio device name. " << SDL_GetError();
			}
		}
	}
	else {
		log_error() << "Could not get number of audio devices. " << SDL_GetError();
	}

	return oss.str();
}

std::string SdlDisplayModes() {
	std::ostringstream oss;

	const int k_num_video_displays = SDL_GetNumVideoDisplays();
		if(k_num_video_displays >= 1) {

			oss << "Display | Mode | Format | Width | Height | Refresh Rate\n";

			for(int i = 0; i < k_num_video_displays; i++) {

				SDL_DisplayMode current_mode;
				const int k_got_current_mode = SDL_GetDesktopDisplayMode(i, &current_mode);
				if (k_got_current_mode == 0){

					const int k_num_display_modes = SDL_GetNumDisplayModes(i);
					if(k_num_display_modes >= 1) {

						SDL_DisplayMode* modes = new
							SDL_DisplayMode[k_num_video_displays * k_num_display_modes];

						for(int j = 0; j < k_num_display_modes; j++) {
							SDL_DisplayMode mode_ij = modes[i + k_num_display_modes * j];

							const int k_got_display_mode = SDL_GetDisplayMode(i, j, &mode_ij);
							if(k_got_display_mode == 0) {
								oss << (i+1) << "\t|" << (j+1) << "\t|" <<
									detail::PixelFormatToString(mode_ij.format) << "\t|" <<
									mode_ij.w << "\t|" << mode_ij.h << "\t|" <<
									mode_ij.refresh_rate;

								if(EqualDisplayModes(current_mode, mode_ij)) {
									oss << " [* CURRENT]";
								}

								oss << "\n";
							}
							else {
								log_error() << "Could not get display mode information. " <<
									SDL_GetError();
							}	
						}

						delete[] modes;
					}
					else {
						log_error() << "Could not get number of display modes. " <<
							SDL_GetError();
					}
				}
				else {
					log_error() << "Could not get current display mode. " << SDL_GetError();
				}
			}
		}
		else {
			log_error() << "Could not get number of video displays. " << SDL_GetError();
		}

	return oss.str();
}

std::string RendererInfoToString(const SDL_RendererInfo& info) {
	std::ostringstream oss;

	oss << info.name << ": [" << RendererFlagsToString(info.flags) <<
		"] renderer flags, " << info.max_texture_width << "/" << info.max_texture_height <<
		" as max width/height, formats: ";

	for(int i = 0; i < static_cast<int>(info.num_texture_formats); i++) {
		oss << PixelFormatToString(info.texture_formats[i]) << ", ";
	}

	return oss.str();
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

std::string RendererFlagsToString(const Uint32 flags) {
	std::ostringstream oss;

	if(flags & SDL_RENDERER_SOFTWARE) {
		oss << "SOFTWARE,";
	}

	if(flags & SDL_RENDERER_ACCELERATED) {
		oss << "ACCELERATED,";
	}

	if(flags & SDL_RENDERER_PRESENTVSYNC) {
		oss << "PRESENTVSYNC,";
	}

	if(flags & SDL_RENDERER_TARGETTEXTURE) {
		oss << "TARGETTEXTURE,";
	}

	return oss.str();
}

bool EqualDisplayModes(const SDL_DisplayMode& first, const SDL_DisplayMode& second) {
	return ((first.format == second.format) && (first.w == second.w) && (first.h == second.h)
		&& (first.refresh_rate == second.refresh_rate));
}

} // namespace detail
} // namespace sdl
