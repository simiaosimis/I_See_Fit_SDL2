#include "AudioHandler.h"
#include "Game.h"
#include "Logger.h"
#include "UsefulDefines.h"

AudioHandler::AudioHandler() :
	currentMusic(nullptr),
	currentEffects()
{

}

AudioHandler::~AudioHandler() {
	this->currentEffects.clear();
}

void AudioHandler::changeMusic(const std::string& path_, const int times_) {
	stopMusic();
	setCurrentMusic(path_);
	playMusic(times_);
}

void AudioHandler::pushSoundEffect(const std::string& path_, const int times_) {
	SoundEffect* sfx = Game::instance().getSoundEffect(path_);
	this->currentEffects.push_back(sfx);
	playEffect(times_);
}

void AudioHandler::pauseMusic() {
	const int musicIsPlaying = Mix_PlayingMusic();
	if(musicIsPlaying == 1) {
		Mix_PauseMusic();
	}
	else {
		Log(WARN) << "Trying to pause music that is not playing.";
	}
}

void AudioHandler::pauseEffects() {
	Mix_Pause(ALL_CHANNELS);
}

void AudioHandler::resumeMusic() {
	Mix_ResumeMusic();
}

void AudioHandler::resumeEffects() {
	Mix_Resume(ALL_CHANNELS);
}

void AudioHandler::setVolumeMusic(const unsigned int percent_) {
	// No need to check for percent_ being above 100, SDL_Mixer already caps the volume to
	// MIX_MAX_VOLUME.
	const int value = percent_ * MIX_MAX_VOLUME/100;
	Mix_VolumeMusic(value);
}

void AudioHandler::setVolumeEffects(const unsigned int percent_) {
	// No need to check for percent_ being above 100, SDL_Mixer already caps the volume to
	// MIX_MAX_VOLUME.
	const int value = percent_ * MIX_MAX_VOLUME/100;
	Mix_Volume(ALL_CHANNELS, value);
}

void AudioHandler::playEffect(const int times_) {
	const int playedChannel = Mix_PlayChannel(-1, this->currentEffects.back()->getMixChunk(),
		times_);

	if(playedChannel == -1) {
		Log(ERROR) << "Failed to play sound effect on channel " << playedChannel << ". "
			<< Mix_GetError();
	}

	this->currentEffects.back()->channel = playedChannel;

	Mix_ChannelFinished(AudioHandler::channelDone);
}

void AudioHandler::stopMusic() {
	Mix_HaltMusic();
}

void AudioHandler::setCurrentMusic(const std::string& path_) {
	this->currentMusic = Game::instance().getMusic(path_);
}

void AudioHandler::playMusic(const int times_) {
	if(this->currentMusic != nullptr) {
		const int playedMusic = Mix_PlayMusic(this->currentMusic->getMixMusic(), times_);

		if(playedMusic == -1) {
			Log(ERROR) << "Couldn't play music (" << this->currentMusic->getPath() << "). "
				<< Mix_GetError();
		}
	}
	else {
		Log(ERROR) << "Can't play a null music.";
	}
}

void AudioHandler::clearChannel(const int channel_) {
	std::vector<SoundEffect*>::iterator it;

	for(it = this->currentEffects.begin(); it != this->currentEffects.end();) {
		if((*it)->channel == channel_) {
			this->currentEffects.erase(it);
		}
		else {
			it++;
		}
	}
}

void AudioHandler::channelDone(int channel_) {
	Game::instance().getAudioHandler().clearChannel(channel_);
}
