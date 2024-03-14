#include "object.h"
Object::Object(string sprite_src_path, int x_pos, int y_pos, int x_velocity, int y_velocity, SDL_Renderer* renderer) {
	sprite_src = sprite_src_path;
	sprite_rect.x = x_pos;
	sprite_rect.y = y_pos;
	x_vel = 0;
	y_vel = 0;
	this->x_velocity = x_velocity;
	this->y_velocity = y_velocity;
	objectTexture.set_renderer(renderer);
	objectTexture.LoadFileImage(sprite_src);
}
Object::~Object() {
	objectTexture.free();
}
int Object::getX() {
	return sprite_rect.x;
}
int Object::getY() {
	return sprite_rect.y;
}
void Object::setClip(int x, int y, int w, int h) {
	sprite_clip.x = x;
	sprite_clip.y = y;
	sprite_clip.h = h;
	sprite_clip.w = w;

	sprite_rect.h = h;
	sprite_rect.w = w;
}
void Object::setMapSize(int w, int h) {
	map_width = w;
	map_height = h;
}
void Object::HandleEvent(SDL_Event& e) {
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
			case SDLK_UP:
				y_vel -= y_velocity;
				break;
			case SDLK_DOWN:
				y_vel += y_velocity;
				break;
			case SDLK_RIGHT:
				x_vel += x_velocity;
				break;
			case SDLK_LEFT:
				x_vel -= x_velocity;
				break;
			default:
				break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
			case SDLK_UP:
				y_vel += y_velocity;
				break;
			case SDLK_DOWN:
				y_vel -= y_velocity;
				break;
			case SDLK_RIGHT:
				x_vel -= x_velocity;
				break;
			case SDLK_LEFT:
				x_vel += x_velocity;
				break;
			default:
				break;
		}
	}
}
void Object::move() {
	sprite_rect.x += x_vel;
	sprite_rect.y += y_vel;
	if (sprite_rect.x < 0 || sprite_rect.x + sprite_rect.w > map_width) {
		sprite_rect.x -= x_vel;
	}
	if (sprite_rect.x < 0 || sprite_rect.x + sprite_rect.w > map_width) {
		sprite_rect.y -= y_vel;
	}
}
void Object::render(int camX, int camY) {
	objectTexture.render(sprite_rect.x - camX, sprite_rect.y - camY,&sprite_clip);
}