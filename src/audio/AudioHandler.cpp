#include "AudioHandler.h"
#include <algorithm>
#include "engine/Game.h"
#include "util/Logger.h"
#include "util/Assert.h"

namespace sdl2engine {

AudioHandler::AudioHandler() :
	m_current_music{nullptr},
	m_effects{}
{
	Mix_ChannelFinished(AudioHandler::ChannelDone);
}

AudioHandler::~AudioHandler() {
	/// @todo Is clearing the this vector necessary?
	m_effects.clear();
}

void AudioHandler::ChangeMusic(const std::string& path) {
	StopMusic();
	SetMusic(path);
	PlayMusic();
}

void AudioHandler::ChangeMusic(const std::string& path, const int times) {
	ASSERT(times >= 1, "Must be >= 1");
	StopMusic();
	SetMusic(path);
	PlayMusic(times);
}

void AudioHandler::PlaySoundEffect(const std::string& path) {
	m_effects.push_back(Game::Instance().Resource().soundEffect(path));

	const int k_play_once = 0;
	const int k_played_channel = Mix_PlayChannel(k_any_channel, m_effects.back()->MixChunk(),
		k_play_once);
	if(k_played_channel == -1) {
		log_error() << "Failed to play sound effect on channel " << k_played_channel << ". "
			<< Mix_GetError();
	}

	m_effects.back()->m_channel = k_played_channel;
}

void AudioHandler::PlaySoundEffect(const std::string& path, const int times) {
	ASSERT((times == k_infinite_loop || times >= 2), "Must be k_infinite_loop or >= 2. If only needed to play once, use AudioHandler::PlaySoundEffect(const std::string&)");

	m_effects.push_back(Game::Instance().Resource().soundEffect(path));

	const int k_played_channel = Mix_PlayChannel(k_any_channel, m_effects.back()->MixChunk(),
		(times - 1));
	if(k_played_channel == -1) {
		log_error() << "Failed to play sound effect on channel " << k_played_channel << ". "
			<< Mix_GetError();
	}

	m_effects.back()->m_channel = k_played_channel;
}

void AudioHandler::SetMusicVolume(const int percent) {
	/// @todo Decide whether the <= 100 assertion is necessary.
	// No need to check for percent being above 100, SDL_Mixer already caps the volume to
	// MIX_MAX_VOLUME.
	ASSERT(percent >= 0  , "Must be >= 0");
	ASSERT(percent <= 100, "Must be <= 100");
	const int k_volume_value = percent * MIX_MAX_VOLUME/100;
	Mix_VolumeMusic(k_volume_value);
}

void AudioHandler::SetEffectsVolume(const int percent) {
	/// @todo Decide whether the <= 100 assertion is necessary.
	// No need to check for percent being above 100, SDL_Mixer already caps the volume to
	// MIX_MAX_VOLUME.
	ASSERT(percent >= 0  , "Must be >= 0");
	ASSERT(percent <= 100, "Must be <= 100");
	const int k_volume_value = percent * MIX_MAX_VOLUME/100;
	Mix_Volume(k_all_channels, k_volume_value);
}

void AudioHandler::PauseMusic() {
	const int k_music_is_playing = Mix_PlayingMusic();
	if(k_music_is_playing == 1) {
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

void AudioHandler::PlayMusic() {
	if(m_current_music != nullptr) {
		const int k_played_music = Mix_PlayMusic(m_current_music->MixMusic(), k_infinite_loop);

		if(k_played_music == -1) {
			log_error() << "Couldn't play music (" << m_current_music->Path() << "). "
				<< Mix_GetError();
		}
	}
	else {
		log_error() << "Can't play a null music.";
	}
}

void AudioHandler::PlayMusic(const int times) {
	ASSERT(times >= 1, "Must be >= 1");
	if(m_current_music != nullptr) {
		const int k_played_music = Mix_PlayMusic(m_current_music->MixMusic(), times);

		if(k_played_music == -1) {
			log_error() << "Couldn't play music (" << m_current_music->Path() << "). "
				<< Mix_GetError();
		}
	}
	else {
		log_error() << "Can't play a null music.";
	}
}

void AudioHandler::StopMusic() {
	Mix_HaltMusic();
}

void AudioHandler::SetMusic(const std::string& path) {
	m_current_music = Game::Instance().Resource().music(path);
}

void AudioHandler::ClearChannel(const int channel) {
	std::vector<SoundEffect*>::iterator it = std::remove_if(m_effects.begin(), m_effects.end(),
		[=](SoundEffect* se){ return se->m_channel == channel; });
	m_effects.erase(it, m_effects.end());
}

void AudioHandler::ChannelDone(const int channel) {
	Game::Instance().GetAudioHandler().ClearChannel(channel);
}

} // namespace sdl2engine
