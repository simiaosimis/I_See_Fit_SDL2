#include "engine/GameObject.h"
#include "core/ResourceManager.h"
#include "graphics/Sprite.h"
#include "util/Logger.h"
#include "util/Assert.h"

namespace sdl2engine {

GameObject::GameObject(const double x, const double y, const std::string& path) :
    m_x{x},
    m_y{y},
    m_sprite{ResourceManager<Sprite>::Instance().Get(path)},
    m_width{0},
    m_height{0},
    m_animation_clip{0, 0, 0, 0},
    m_bounding_box{static_cast<int>(x), static_cast<int>(y), 0, 0}
{
    if(m_sprite != nullptr) {
        m_width = m_sprite->Width();
        m_height = m_sprite->Height();

        m_bounding_box.w = m_width;
        m_bounding_box.h = m_height;
    }
    else {
        log_warn() << "GameObject sprite is null, width and height will be undefined.";
    }

    ASSERT(m_width >= 0 , "Must be >= 0");
    ASSERT(m_height >= 0, "Must be >= 0");
}

double GameObject::X() {
    return m_x;
}

double GameObject::Y() {
    return m_y;
}

int GameObject::Width() {
    return m_width;
}

int GameObject::Height() {
    return m_height;
}

SDL_Rect& GameObject::AnimationClip() {
    return m_animation_clip;
}

SDL_Rect& GameObject::BoundingBox() {
    return m_bounding_box;
}

void GameObject::SetX(const double x) {
    m_x = x;
}

void GameObject::SetY(const double y) {
    m_y = y;
}

} // namespace sdl2engine
