#include "graphics/Sprite.h"
#include "engine/Game.h"
#include "util/Logger.h"
#include "util/Assert.h"

Sprite::Sprite(const std::string& path) :
	m_sdl_texture{nullptr},
	m_width{0},
	m_height{0},
	m_path{path}
{
	LoadFrom(m_path);

	SetBlendMode(SDL_BLENDMODE_BLEND);
	SetAlpha(255);

	ASSERT(m_width >= 0 , "Must be >= 0");
	ASSERT(m_height >= 0, "Must be >= 0");
}

Sprite::Sprite(SDL_Surface* const surface) :
	m_sdl_texture{SurfaceToTexture(surface)},
	m_width{0},
	m_height{0},
	m_path{"font"}
{
	// Display error log if image wasn't loaded.
	if(m_sdl_texture == nullptr) {
		log_error() << "Sprite load failed: " << m_path;
	}

	ASSERT(m_width >= 0 , "Must be >= 0");
	ASSERT(m_height >= 0, "Must be >= 0");
}

Sprite::~Sprite() {
	if(m_sdl_texture != nullptr) {
		SDL_DestroyTexture(m_sdl_texture);
		m_sdl_texture = nullptr;
	}
}

void Sprite::LoadFrom(const std::string& path) {
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if(loadedSurface != nullptr) {
		m_sdl_texture = SurfaceToTexture(loadedSurface);
	}
	else {
		log_error() << "Could not load surface from path." << IMG_GetError();
	}

	// Display error log if image wasn't loaded.
	if(m_sdl_texture == nullptr) {
		log_error() << "Sprite load failed: " << path;
	}
}

void Sprite::Render(const double x, const double y, SDL_Rect* const clip,
	const bool stretch, const double angle, SDL_Point* const center,
	SDL_RendererFlip flip) {

	// This is the destination SDL_Rect structure.
	SDL_Rect renderQuad = {static_cast<int>(x), static_cast<int>(y), m_width, m_height};

	if(clip != nullptr) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	else {
		// Don't clip the sprite.
	}

	int logicalW = 0;
	int logicalH = 0;
	Game::Instance().GetRenderer()->LogicalSize(&logicalW, &logicalH);
	SDL_Rect stretch_rectangle = {static_cast<int>(x), static_cast<int>(y), logicalW,
		logicalH};

	const int successfullRender = (!stretch) ?
		SDL_RenderCopyEx(Game::Instance().GetRenderer()->SdlRenderer(), m_sdl_texture, clip,
			&renderQuad, angle, center, flip) :
		SDL_RenderCopyEx(Game::Instance().GetRenderer()->SdlRenderer(), m_sdl_texture, clip,
			&stretch_rectangle, angle, center, flip);

	if(successfullRender != 0) {
		log_error() << "Failed to render sprite." << SDL_GetError();
	}
}

int Sprite::Width() {
	return m_width;
}

int Sprite::Height() {
	return m_height;
}

void Sprite::SetWidth(int width) {
	ASSERT(width >= 0, "Must be >= 0");
	m_width = width;
}

void Sprite::SetHeight(int height) {
	ASSERT(height >= 0, "Must be >= 0");
	m_height = height;
}

SDL_Texture* Sprite::SurfaceToTexture(SDL_Surface* const surface) {
	ASSERT(Game::Instance().GetRenderer()->SdlRenderer() != nullptr, "Window renderer should not be null!");

	// The final texture.
	SDL_Texture* newTexture = nullptr;

	if(surface != nullptr) {
		// Create texture from the surface pixels.
	    newTexture = SDL_CreateTextureFromSurface(
	    	Game::Instance().GetRenderer()->SdlRenderer(), surface);
		if(newTexture != nullptr) {
			// Set the Sprites width and height, from the loaded surface.
			m_width = surface->w;
			m_height = surface->h;
		}
		else {
			log_error() << "Could not create texture from surface." << SDL_GetError();
		}

		// Free the loaded surface.
		SDL_FreeSurface(surface);
	}
	else {
		log_warn() << "Trying to convert a null surface to a texture.";
	}

	return newTexture;
}

std::string Sprite::Path() {
	return m_path;
}

double Sprite::Alpha() {
	Uint8 alpha = 0;

	const int rc = SDL_GetTextureAlphaMod(m_sdl_texture, &alpha);
	if(rc != 0) {
		log_error() << "Could not get alpha value from Sprite (" << m_path << "). " <<
			SDL_GetError();
	}

	return static_cast<double>(alpha);
}

void Sprite::SetAlpha(int alpha) {
	if(alpha < 0) {
		alpha = 0;
	}
	else if(alpha > 255) {
		alpha = 255;
	}

	const int rc = SDL_SetTextureAlphaMod(m_sdl_texture, alpha);
	if(rc != 0) {
		log_error() << "Could not set alpha value of Sprite (" << m_path << "). " <<
			SDL_GetError();
	}
}

void Sprite::SetBlendMode(SDL_BlendMode blend_mode) {
	const int rc = SDL_SetTextureBlendMode(m_sdl_texture, blend_mode);
	if(rc != 0) {
		log_error() << "Could not set blend mode of Sprite (" << m_path << "). " <<
			SDL_GetError();
	}
}
