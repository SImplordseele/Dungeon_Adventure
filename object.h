#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Texture.h"
class Object {
public:
    Texture objectTexture;
    Object(string sprite_src_path, int x_pos, int y_pos, int x_velocity, int y_velocity, SDL_Renderer* renderer);
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
    SDL_Rect sprite_rect;
    int x_vel, y_vel;
    int x_velocity, y_velocity;
    SDL_Rect sprite_clip;
    int map_width;
    int map_height;
};
