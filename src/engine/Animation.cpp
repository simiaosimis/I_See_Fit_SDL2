#include "Animation.h"
#include "util/Assert.h"

namespace sdl2engine {

Animation::Animation(const int x, const int y, const int sprite_width, const int sprite_height,
		const int number_of_images, const double total_time) :
	m_x{x},
	m_y{y},
	m_initial_x{x},
	m_initial_y{y},
	m_sprite_width{sprite_width},
	m_sprite_height{sprite_height},
	m_number_of_images{(number_of_images == 0) ? 1 : number_of_images},
	m_total_elapsed_time{0.0},
	m_total_time{total_time},
	m_animation_count{0}
{
	ASSERT(m_x >= 0					, "Must be >= 0");
	ASSERT(m_y >= 0					, "Must be >= 0");
	ASSERT(m_initial_x >= 0			, "Must be >= 0");
	ASSERT(m_initial_y >= 0			, "Must be >= 0");
	ASSERT(m_sprite_width >= 0		, "Must be >= 0");
	ASSERT(m_sprite_height >= 0		, "Must be >= 0");
	ASSERT(m_number_of_images >= 1	, "Must be >= 1");
	ASSERT(m_total_elapsed_time >= 0, "Must be >= 0");
	ASSERT(m_total_time >= 0		, "Must be >= 0");
	ASSERT(m_animation_count >= 0	, "Must be >= 0");
}

Animation::~Animation() {
}

void Animation::Update(SDL_Rect& clip, const double delta_time) {
	// Compare the position on the sprite with the number of positions to know if is the
	// end of the animation.
	const bool k_end_of_animation = (CurrentFrame() >= m_number_of_images);
	const double k_time_for_each_frame = (m_total_time / m_number_of_images);

	m_total_elapsed_time += delta_time;

	// Check if the frame has changed.
	if(m_total_elapsed_time >= k_time_for_each_frame) {
		m_total_elapsed_time = 0;
		m_animation_count += 1;

		// Apparently defines the max horizontal sprites in the spritesheet.
		/// @todo Be sure what k_animation_limit does. 
		const int k_animation_limit = 10;
		ASSERT(k_animation_limit >= 0, "Must be >= 0");

		if(m_animation_count <= m_number_of_images) {
			if(m_x < k_animation_limit) {
				m_x += 1;
			}
			else {
				m_y += 1;
				m_x = 0;
			}
		}

		if(k_end_of_animation) {
			m_x = m_initial_x;
			m_y = m_initial_y;
			m_animation_count = 0;
		}
	}

	const int k_position_x = m_x * m_sprite_width;
	const int k_position_y = m_y * m_sprite_height;
	UpdateClip(clip, k_position_x, k_position_y);
}

void Animation::ChangeAnimation(const int x, const int y, const int number_of_images,
		const double total_time) {
	m_x = x;
	m_y = y;
	m_initial_x = x;
	m_initial_y = y;
	m_number_of_images = (number_of_images == 0) ? 1 : number_of_images;
	m_total_time = total_time;
	m_animation_count = 0;

	ASSERT(m_x >= 0				  , "Must be >= 0");
	ASSERT(m_y >= 0				  , "Must be >= 0");
	ASSERT(m_initial_x >= 0		  , "Must be >= 0");
	ASSERT(m_initial_y >= 0		  , "Must be >= 0");
	ASSERT(m_number_of_images >= 1, "Must be >= 1");
	ASSERT(m_total_time >= 0	  , "Must be >= 0");
	ASSERT(m_animation_count >= 0 , "Must be >= 0");
}

void Animation::UpdateClip(SDL_Rect& clip, const int x, const int y) {
	ASSERT(x >= 0, "Must be >= 0");
	ASSERT(y >= 0, "Must be >= 0");

	clip.x = x;
	clip.y = y;
	clip.w = m_sprite_width;
	clip.h = m_sprite_height;
}

int Animation::CurrentFrame() {
	const int k_current_frame = m_animation_count + 1;
	ASSERT(k_current_frame >= 0, "Must be >= 0");
	return k_current_frame;
}

void Animation::SetWidthHeight(const int width, const int height) {
	m_sprite_width = width;
	m_sprite_height = height;

	ASSERT(m_sprite_width >= 0 , "Must be >= 0");
	ASSERT(m_sprite_height >= 0, "Must be >= 0");
}

} // namespace sdl2engine
