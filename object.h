#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Texture.h"
class Object {
public:
	Texture objectTexture;
	Object(string sprite_src_path, int x_pos, int y_pos, int x_vel, int y_vel, SDL_Renderer* renderer);
	~Object();
	int getX();
	int getY();
	void setMapSize(int w, int h);
	void setClip(int x, int y, int w, int h);
	void HandleEvent(SDL_Event& e);
	void move();
	void render(int camX, int camY);
protected:
	string sprite_src;
	//Texture position and size
	SDL_Rect sprite_rect;
	int x_vel, y_vel;
	SDL_Rect sprite_clip;
	int map_width;
	int map_height;
	int x_velocity, y_velocity;
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 320;
};