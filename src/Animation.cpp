#include "Animation.h"

Animation::Animation(const unsigned int x_, const unsigned int y_,
	const unsigned int spriteWidth_, const unsigned int spriteHeight_,
	const unsigned int numberOfImages_, const double totalTime_) :

	x(x_),
	y(y_),
	initialX(x_),
	initialY(y_),
	spriteWidth(spriteWidth_),
	spriteHeight(spriteHeight_),
	numberOfImages(numberOfImages_),
	totalElapsedTime(0.0),
	totalTime(totalTime_),
	animationCount(0)
{
	this->numberOfImages = (numberOfImages_ == 0) ? 1 : numberOfImages_;
}

Animation::~Animation() {

}

void Animation::update(SDL_Rect& clip, const double dt_) {
	// Compare the position on the sprite with the number of positions to know if is the
	// end of the animation.
	const bool endOfAnimation = (getCurrentFrame() >= this->numberOfImages);

	const double timeForEachFrame = (this->totalTime / this->numberOfImages);

	this->totalElapsedTime += dt_;

	// Check if the frame has changed.
	if(this->totalElapsedTime >= timeForEachFrame) {
		this->totalElapsedTime = 0;
		this->animationCount += 1;

		// Apparently defines the max horizontal sprites in the spritesheet.
		const unsigned int animationLimit = 10;

		if(this->animationCount <= this->numberOfImages) {
			if(this->x < animationLimit) {
				this->x += 1;
			}
			else {
				this->y += 1;
				this->x = 0;
			}
		}

		if(endOfAnimation) {
			this->x = this->initialX;
			this->y = this->initialY;
			this->animationCount = 0;
		}
	}

	const unsigned int positionX_ = this->x * this->spriteWidth;
	const unsigned int positionY_ = this->y * this->spriteHeight;

	updateClip(clip, positionX_, positionY_);
}

void Animation::changeAnimation(const unsigned int x_, const unsigned int y_,
	const unsigned int numberOfImages_, const double totalTime_) {

	this->x = x_;
	this->y = y_;
	this->initialX = x_;
	this->initialY = y_;
	this->numberOfImages = (numberOfImages_ == 0) ? 1 : numberOfImages_;
	this->totalTime = totalTime_;
	this->animationCount = 0;
}

void Animation::updateClip(SDL_Rect& clip, const unsigned int x_, const unsigned int y_) {
	clip.x = static_cast<int>(x_);
	clip.y = static_cast<int>(y_);
	clip.w = static_cast<int>(this->spriteWidth);
	clip.h = static_cast<int>(this->spriteHeight);
}

unsigned int Animation::getCurrentFrame() {
	return (this->animationCount + 1);
}

void Animation::changeWidthHeight(const unsigned int width_, const unsigned int height_) {
	this->spriteWidth = width_;
	this->spriteHeight = height_;
}
