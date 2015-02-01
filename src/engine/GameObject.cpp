#include "engine/GameObject.h"
#include <SDL2/SDL.h>
#include "core/ResourceManager.h"
#include "util/Logger.h"
#include "util/Assert.h"

namespace sdl2engine {

GameObject::GameObject(const double x_, const double y_, const std::string& path_) :
    x(x_),
    y(y_),
    isRight(true),
    sprite(ResourceManager<Sprite>::Instance().Get(path_)),
    width(0),
    height(0),
    animationClip{0, 0, 0, 0},
    boundingBox{static_cast<int>(x_), static_cast<int>(y_), 0, 0}
{
    // Only serves as the initializer for the derived classes.

    if(this->sprite != nullptr) {
        this->width = this->sprite->Width();
        this->height = this->sprite->Height();

        this->boundingBox.w = this->width;
        this->boundingBox.h = this->height;
    }
    else {
        log_warn() << "GameObject sprite is null, width and height will be undefined.";
    }

    ASSERT(width >= 0 , "Must be >= 0");
    ASSERT(height >= 0, "Must be >= 0");
}

GameObject::GameObject(const double x_, const double y_) :
    x(x_),
    y(y_),
    isRight(true),
    sprite(nullptr),
    width(0),
    height(0),
    animationClip{0, 0, 0, 0},
    boundingBox{static_cast<int>(x_), static_cast<int>(y_), 0, 0}
{
    // Only serves as the initializer for the derived classes.
}

GameObject::~GameObject() {

}

int GameObject::getWidth() {
	return this->width;
}

int GameObject::getHeight() {
	return this->height;
}

SDL_Rect& GameObject::getAnimationClip() {
	return this->animationClip;
}

SDL_Rect& GameObject::getBoundingBox() {
    return this->boundingBox;
}

} // namespace sdl2engine
