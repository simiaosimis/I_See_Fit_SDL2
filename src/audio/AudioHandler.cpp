#include "audio/AudioHandler.h"
#include <SDL2/SDL_mixer.h>
#include "audio/Music.h"
#include "audio/SoundEffect.h"
#include "core/ResourceManager.h"
#include "util/Logger.h"
#include "util/Assert.h"

namespace {

static constexpr auto k_all_channels = -1; /**< Act on all sound effects channels. */
static constexpr auto k_any_channel = -1; /**< Use any sound effects channel. */

} // namespace

namespace sdl2engine {

// ----------------------------------------------------------- //
//                       Music Handling
// ----------------------------------------------------------- //

template <>
void AudioHandler<AudioType::Music>::Play(const std::string& path, const int times) {
	ASSERT((times == k_infinite_loop || times >= 1), "Must be k_infinite_loop or >= 1.");

	const auto music = ResourceManager<Music>::Instance().Get(path);
	ASSERT(music != nullptr, "Shouldn't be playing null music.");

	const auto k_played_music = (Mix_PlayMusic(music->MixMusic(), times) == 0);
	if(!k_played_music) {
		log_error() << "Couldn't play music (" << music->Path() << "). "
			<< Mix_GetError();
	}
}

template <>
void AudioHandler<AudioType::Music>::SetVolume(const int percent) {
	/// @todo Decide whether the <= 100 assertion is necessary.
	// No need to check for percent being above 100, SDL_Mixer already caps the volume to
	// MIX_MAX_VOLUME.
	ASSERT(percent >= 0  , "Must be >= 0");
	ASSERT(percent <= 100, "Must be <= 100");

	const auto k_volume_value = percent * MIX_MAX_VOLUME/100;
	Mix_VolumeMusic(k_volume_value);
}

template <>
void AudioHandler<AudioType::Music>::Pause() {
	Mix_PauseMusic();
}

template <>
void AudioHandler<AudioType::Music>::Resume() {
	Mix_ResumeMusic();
}

template <>
void AudioHandler<AudioType::Music>::Stop() {
	Mix_HaltMusic();
}

template <>
void AudioHandler<AudioType::Music>::FadeOut(const double seconds) {
	const auto k_milliseconds = static_cast<int>(seconds*1000);
	const auto k_faded = (Mix_FadeOutMusic(k_milliseconds) == 1);
	if(!k_faded) {
		log_warn() << "Could not fade music. Probably no music playing/already faded.";
	}
}

template <>
bool AudioHandler<AudioType::Music>::FadedOut() {
	const auto k_fading = (Mix_FadingMusic() == MIX_FADING_OUT);
	const auto k_playing = (Mix_PlayingMusic() == 1);
	return !k_fading && !k_playing;
}

// ----------------------------------------------------------- //
//                    Sound Effects Handling
// ----------------------------------------------------------- //

template <>
void AudioHandler<AudioType::SoundEffect>::Play(const std::string& path, const int times) {
	ASSERT((times == k_infinite_loop || times >= 1), "Must be k_infinite_loop or >= 1.");

	const auto k_played_channel = Mix_PlayChannel(k_any_channel,
		ResourceManager<SoundEffect>::Instance().Get(path)->MixChunk(), (times - 1));
	if(k_played_channel == -1) {
		log_error() << "Failed to play sound effect for any channel (" << k_played_channel <<
			"). " << Mix_GetError();
	}
}

template <>
void AudioHandler<AudioType::SoundEffect>::SetVolume(const int percent) {
	/// @todo Decide whether the <= 100 assertion is necessary.
	// No need to check for percent being above 100, SDL_Mixer already caps the volume to
	// MIX_MAX_VOLUME.
	ASSERT(percent >= 0  , "Must be >= 0");
	ASSERT(percent <= 100, "Must be <= 100");

	const auto k_volume_value = percent * MIX_MAX_VOLUME/100;
	Mix_Volume(k_all_channels, k_volume_value);
}

template <>
void AudioHandler<AudioType::SoundEffect>::Pause() {
	Mix_Pause(k_all_channels);
}

template <>
void AudioHandler<AudioType::SoundEffect>::Resume() {
	Mix_Resume(k_all_channels);
}

template <>
void AudioHandler<AudioType::SoundEffect>::Stop() {
	Mix_HaltChannel(k_all_channels);
}

template <>
void AudioHandler<AudioType::SoundEffect>::FadeOut(const double seconds) {
	const auto k_milliseconds = static_cast<int>(seconds*1000);
	Mix_FadeOutChannel(k_all_channels, k_milliseconds);
}

// template <>
// bool AudioHandler<AudioType::SoundEffect>::FadedOut() {
// 	return false;
// }

} // namespace sdl2engine
