#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Texture.h"
#include "Object.h"
#include "Player.h"
#include "Key.h"
#include "Map.h"
extern const string Help_document;
extern string Help(string);
class Level {
public:
    static int lv;
    Level(int cam_w, int cam_h, SDL_Window* window, SDL_Renderer* renderer, Player* player);
    ~Level();
    void SetLevel(int x, int y);
    SDL_Texture* LoadTexture(string path);
    void LoadLevel(Map* level);
    int PlayLevel();
    void print_text();
    void setuptext(int x);
    SDL_Texture* SetText(string text);
private:
    Texture text[2];
    TTF_Font* font = NULL;
    SDL_Color text_color = { 255,255,255 };
    int LEVEL_WIDTH;
    int LEVEL_HEIGHT;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    Map* level = NULL;
    Player* player = NULL;
    SDL_Rect cam;
};
