#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "Texture.h"
const int BUTTON_TOTAL = 3;
const int BUTTON_WIDTH = 155;
const int BUTTON_HEIGHT = 100;
const int main_menu = 0;
const int start = 1;
const int help = 2;
const int Exit = 3;
const int Won = 4;
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
private:
    int menu_width;
    int menu_height;
    TTF_Font* menu_font;
    SDL_Window* menu_window;
    SDL_Renderer* menu_renderer;
    Button* menu_Button;
    SDL_Color buttonColor[2] = { {255, 255, 255}, {105, 105, 105} };
    SDL_Texture* title;
    SDL_Rect title_pos;
};

