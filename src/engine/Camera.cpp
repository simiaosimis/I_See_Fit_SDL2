#include "engine/Camera.h"
#include <cassert>
#include "engine/GameObject.h"
#include "util/Configuration.h"

Camera::Camera(GameObject* const game_object):
	m_game_object{game_object},
	m_level_width{0},
	m_level_height{0},
	m_clip{0, 0, Configuration::CameraDistanceWidth(), Configuration::CameraDistanceHeight()}
{

}

Camera::~Camera() {

}

void Camera::Update() {
	UpdatePosition();
}

SDL_Rect& Camera::Clip() {
	return m_clip;
}

void Camera::UpdatePosition() {
	m_clip.x = (m_game_object->x + m_game_object->getWidth() / 2) - (m_clip.w / 2);
	m_clip.y = (m_game_object->y + m_game_object->getHeight() / 2) - (m_clip.h / 2);

	// Left wall.
	if(m_clip.x < 0) {
		m_clip.x = 0;
	}
	// Right wall.
	else if(m_clip.x > m_level_width - m_clip.w) {
		m_clip.x = m_level_width - m_clip.w;
	}
	// Top wall.
	if(m_clip.y < 0) {
		m_clip.y = 0;
	}
	// Bottom wall.
	else if(m_clip.y > m_level_height - m_clip.h) {
		m_clip.y = m_level_height - m_clip.h;
	}
}

void Camera::CentralizeOn(GameObject* const game_object) {
	m_game_object = game_object;
}

void Camera::SetLevelDimensions(const int width, const int height) {
	assert(width >= 0 && "Must be >= 0");
	assert(height >= 0 && "Must be >= 0");
	m_level_width = width;
	m_level_height = height;
}