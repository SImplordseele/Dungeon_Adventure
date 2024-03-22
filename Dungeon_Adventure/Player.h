#pragma once
#include "soundeffect.h"
#include "object.h"
#include "Map.h"
#include "Key.h"
const int Player_sprite_width = 64;
const int Player_sprite_height = 96;
const int TOTAL_KEY = 3;
const int TOTAL_PLAYER_SPRITE = 8;
const int DOOR_X = 1920;
const int DOOR_Y = 384;
const int walk_freely = 0;
const int touch_wall = 1;
const int fall_hole = 2;
const int falling = -1;
const int pixelchangerperpress = 1;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
class Key;
class Player : public Object {
public:
    Player(string path, int x_pos, int y_pos, int x_velocity, int y_velocity, SDL_Renderer* renderer, Map* level = NULL);
    ~Player();
    void LoadPlayer();
    void SetlevelMap(Map* level);
    void SetPlayerPos(int x_pos, int y_pos);
    void HandleEvent(SDL_Event& e, Key& key1, Key& key2, Key& key3);
    bool check_collision(SDL_Rect a, SDL_Rect b);
    int collide_with_wall(Tile* tiles[], int tiles_number, int TILE_FLOOR, int TILE_HOLE);
    int move_Player();
    void setCam(SDL_Rect& cam, int w, int h);
    void pickupKey(Key& key);
    bool open_door(SDL_Event& e);
    void render(int camX, int camY);
    void resetkey();
    Sound spotify;
private:
    SDL_Rect clip_left[TOTAL_PLAYER_SPRITE];
    SDL_Rect clip_right[TOTAL_PLAYER_SPRITE];
    SDL_Rect clip_up[TOTAL_PLAYER_SPRITE];
    SDL_Rect clip_down[TOTAL_PLAYER_SPRITE];
    int curr_frame;
    SDL_Rect curr_sprite;
    int startX, startY;
    Map* level;
    int picked_key_number;
    int dx1[4] = { 0,96,0,-96 };
    int dx2[4] = { 96,192,96,0 };
    int dy1[4] = { -96,0,96,0 };
    int dy2[4] = { 0,96,192,96 };
};