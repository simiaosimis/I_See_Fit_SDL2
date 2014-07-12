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

void AudioHandler::stopMusic() {
	Mix_HaltMusic();
}

void AudioHandler::setMusicVolume(const unsigned int percent_) {
	const int value = percent_ * MIX_MAX_VOLUME/100;
	Mix_VolumeMusic(value);
}

void AudioHandler::addSoundEffect(const std::string& path_) {
	SoundEffect* sfx = Game::instance().getSoundEffect(path_);
	this->currentEffects.push_back(sfx);
	playEffect(0);
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

void AudioHandler::setEffectVolume(const unsigned int percent_) {
	const int value = percent_ * MIX_MAX_VOLUME/100;
	Mix_Volume(-1, value);
}

void AudioHandler::changeMusic(const std::string& path_) {
	stopMusic();
	setCurrentMusic(path_);
	playMusic(MIX_LOOP);
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
