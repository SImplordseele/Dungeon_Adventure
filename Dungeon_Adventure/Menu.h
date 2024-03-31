#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "Texture.h"
#include <SDL_mixer.h>
const int BUTTON_TOTAL = 3;
const int BUTTON_WIDTH = 155;
const int BUTTON_HEIGHT = 100;
const int main_menu = 0;
const int lv1 = 1;
const int lv2 = 2;
const int lv3 = 3;
const int lv4 = 4;
const int lv5 = 5;
const int help = 7;
const int quit = 8;
const int win = 9;
extern int lv;
struct Button {
public:
    string Text;
    bool hover = false;
    SDL_Texture* texture;
    SDL_Rect position;
};
class Menu {
public:
    Menu(int w, int h, SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font);
    ~Menu();
    SDL_Texture* setTexture(TTF_Font* font, string text, SDL_Color color);
    void setupMenu();
    int showMenu();
    int showHelp();
    int showFall();
private:
    Texture cursor[2];
    Mix_Chunk* mouse_click;
    int menu_width;
    int menu_height;
    Texture help_menu;
    TTF_Font* menu_font;
    SDL_Window* menu_window;
    SDL_Renderer* menu_renderer;
    Button* menu_Button;
    Button* fall;
    SDL_Color fall_color = { 255,0,0 };
    SDL_Color name = { 128,0,128 };
    SDL_Color buttonColor[2] = { {255, 255, 255}, {144, 238, 144} };
    SDL_Texture* title;
    SDL_Rect title_pos;
    SDL_Texture* title_fall;
    SDL_Rect title_fall_pos;
};

