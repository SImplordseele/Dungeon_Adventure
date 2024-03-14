#include "Key.h"
Key::Key(string path, int x_pos, int y_pos, int x_velocity, int y_velocity, SDL_Renderer* renderer) : 
	Object(path, x_pos, y_pos, x_velocity, y_velocity, renderer) {
	picked = false;
	setClip(0, 0, KEY_WIDTH, KEY_HEIGHT);
}
Key::~Key() {
	objectTexture.free();
}
SDL_Rect Key::get_rect() {
	return sprite_rect;
}
bool Key::Ispicked() {
	return picked;
}
void Key::pick() {
	picked = true;
}
bool Key::check_collision(SDL_Rect a, SDL_Rect b) {
	int left_a, left_b;
	int right_a, right_b;
	int top_a, top_b;
	int bottom_a, bottom_b;
	left_a = a.x; right_a = a.x + a.w;
	left_b = b.x; right_b = b.x + b.w;
	top_a = a.y; bottom_a = a.y + a.h;
	top_b = b.y; bottom_b = b.y + b.h;
	if (left_a >= right_b || left_b >= right_a || top_a >= bottom_b || top_b >= bottom_a) return false;
	return true;
}
void Key::render(SDL_Rect& cam) {
	if (picked == false) {
		if (check_collision(sprite_rect, cam)) {
			objectTexture.render(sprite_rect.x - cam.x, sprite_rect.y - cam.y, &sprite_clip);
		}
	}
}