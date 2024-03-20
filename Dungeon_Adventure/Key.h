#pragma once
#include "object.h"
#include "Player.h"
const int KEY_HEIGHT = 96;
const int KEY_WIDTH = 96;
class Key : public Object {
public:
	Key(string path, int x, int y, int x_velocity, int y_velocity, SDL_Renderer* renderer);
	~Key();
	SDL_Rect get_rect();
	bool Ispicked();
	void pick();
	bool check_collision(SDL_Rect a, SDL_Rect b);
	void render(SDL_Rect& cam);
private:
	bool picked;
};