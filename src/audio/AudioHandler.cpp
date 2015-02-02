#include "audio/AudioHandler.h"
#include <SDL2/SDL_mixer.h>
#include <algorithm>
#include "audio/Music.h"
#include "audio/SoundEffect.h"
#include "core/ResourceManager.h"
#include "util/Logger.h"
#include "util/Assert.h"

namespace sdl2engine {

void AudioHandler::ChangeMusic(const std::string& path) {
	ChangeMusic(path, k_infinite_loop);
}

void AudioHandler::ChangeMusic(const std::string& path, const int times) {
	ASSERT((times == k_infinite_loop || times >= 1), "Must be k_infinite_loop or >= 1.");
	StopMusic();
	PlayMusic(path, times);
}

void AudioHandler::PlaySoundEffect(const std::string& path) {
	PlaySoundEffect(path, 1);
}

void AudioHandler::PlaySoundEffect(const std::string& path, const int times) {
	ASSERT((times == k_infinite_loop || times >= 1), "Must be k_infinite_loop or >= 1.");

	const auto k_played_channel = Mix_PlayChannel(k_any_channel,
		ResourceManager<SoundEffect>::Instance().Get(path)->MixChunk(), (times - 1));
	if(k_played_channel == -1) {
		log_error() << "Failed to play sound effect for any channel (" << k_played_channel <<
			"). " << Mix_GetError();
	}
}

void AudioHandler::SetMusicVolume(const int percent) {
	/// @todo Decide whether the <= 100 assertion is necessary.
	// No need to check for percent being above 100, SDL_Mixer already caps the volume to
	// MIX_MAX_VOLUME.
	ASSERT(percent >= 0  , "Must be >= 0");
	ASSERT(percent <= 100, "Must be <= 100");

	const auto k_volume_value = percent * MIX_MAX_VOLUME/100;
	Mix_VolumeMusic(k_volume_value);
}

void AudioHandler::SetEffectsVolume(const int percent) {
	/// @todo Decide whether the <= 100 assertion is necessary.
	// No need to check for percent being above 100, SDL_Mixer already caps the volume to
	// MIX_MAX_VOLUME.
	ASSERT(percent >= 0  , "Must be >= 0");
	ASSERT(percent <= 100, "Must be <= 100");

	const auto k_volume_value = percent * MIX_MAX_VOLUME/100;
	Mix_Volume(k_all_channels, k_volume_value);
}

void AudioHandler::PauseMusic() {
	const auto k_music_is_playing = (Mix_PlayingMusic() == 1);
	if(k_music_is_playing) {
		Mix_PauseMusic();
	}
	else {
		log_warn() << "Trying to pause music that is not playing.";
	}
}

void AudioHandler::PauseEffects() {
	Mix_Pause(k_all_channels);
}

void AudioHandler::ResumeMusic() {
	Mix_ResumeMusic();
}

void AudioHandler::ResumeEffects() {
	Mix_Resume(k_all_channels);
}

void AudioHandler::PlayMusic(const std::string& path) {
	PlayMusic(path, k_infinite_loop);
}

void AudioHandler::PlayMusic(const std::string& path, const int times) {
	ASSERT((times == k_infinite_loop || times >= 1), "Must be k_infinite_loop or >= 1.");

	const auto music = ResourceManager<Music>::Instance().Get(path);
	ASSERT(music != nullptr, "Shouldn't be playing null music.");

	const auto k_played_music = (Mix_PlayMusic(music->MixMusic(), times) == 0);
	if(!k_played_music) {
		log_error() << "Couldn't play music (" << music->Path() << "). "
			<< Mix_GetError();
	}
}

void AudioHandler::StopMusic() {
	Mix_HaltMusic();
}

} // namespace sdl2engine
