#include "Camera.h"
#include "Configuration.h"

Camera::Camera(GameObject* const gameObject_):
	gameObject(gameObject_),
	levelW(0),
	levelH(0),
	clip{0, 0, static_cast<int>(Configuration::getCameraDistanceWidth()),
		static_cast<int>(Configuration::getCameraDistanceHeight())}
{

}

Camera::~Camera() {

}

void Camera::update() {
	updatePosition();
}

SDL_Rect& Camera::getClip() {
	return this->clip;
}

void Camera::updatePosition() {
	this->clip.x = (this->gameObject->x + this->gameObject->getWidth() / 2) - (this->clip.w / 2);
	this->clip.y = (this->gameObject->y + this->gameObject->getHeight() / 2) - (this->clip.h / 2);

	// Left wall.
	if(this->clip.x < 0) {
		this->clip.x = 0;
	}
	// Right wall.
	else if(this->clip.x > static_cast<int>(this->levelW) - this->clip.w) {
		this->clip.x = static_cast<int>(this->levelW) - this->clip.w;
	}
	// Top wall.
	if(this->clip.y < 0) {
		this->clip.y = 0;
	}
	// Bottom wall.
	else if(this->clip.y > static_cast<int>(this->levelH) - this->clip.h) {
		this->clip.y = static_cast<int>(this->levelH) - this->clip.h;
	}
}

void Camera::centralizeOn(GameObject* const gameObject_) {
	this->gameObject = gameObject_;
}

void Camera::setLevelWH(const unsigned int width_, const unsigned int height_) {
	this->levelW = width_;
	this->levelH = height_;
}
