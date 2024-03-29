#include "Menu.h"
Menu::Menu(int w, int h, SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font) {
    menu_width = w;
    menu_height = h;
    menu_window = window;
    menu_renderer = renderer;
    this->menu_font = font;
    menu_Button = new Button[BUTTON_TOTAL];
    fall = new Button[3];
    mouse_click = Mix_LoadWAV("Sound/mouse-click.wav");
}
Menu::~Menu() {
    delete[]menu_Button;
    delete[]fall;
    menu_font = NULL;
    menu_window = NULL;
    menu_renderer = NULL;
    title = NULL;
}
SDL_Texture* Menu::setTexture(TTF_Font* font, string text, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(menu_renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}
void Menu::setupMenu() {
    menu_Button[0].Text = "Start";
    menu_Button[0].hover = false;
    menu_Button[0].position.x = 90;
    menu_Button[0].position.y = 200;
    menu_Button[0].position.w = BUTTON_WIDTH;
    menu_Button[0].position.h = BUTTON_HEIGHT;
    menu_Button[0].texture = setTexture(menu_font, menu_Button[0].Text, buttonColor[0]);
    menu_Button[1].Text = "Help";
    menu_Button[1].hover = false;
    menu_Button[1].position.x = 242;
    menu_Button[1].position.y = 300;
    menu_Button[1].position.w = BUTTON_WIDTH;
    menu_Button[1].position.h = BUTTON_HEIGHT;
    menu_Button[1].texture = setTexture(menu_font, menu_Button[1].Text, buttonColor[0]);
    menu_Button[2].Text = "Exit";
    menu_Button[2].hover = false;
    menu_Button[2].position.x = 400;
    menu_Button[2].position.y = 200;
    menu_Button[2].position.w = BUTTON_WIDTH;
    menu_Button[2].position.h = BUTTON_HEIGHT;
    menu_Button[2].texture = setTexture(menu_font, menu_Button[2].Text, buttonColor[0]);
    title = setTexture(menu_font, "DUNGEON ADVENTURE", buttonColor[0]);
    title_pos.x = 100;
    title_pos.y = 50;
    title_pos.w = 440;
    title_pos.h = 150;
    help_menu.set_renderer(menu_renderer);
    help_menu.LoadFileImage("Sprites/Untitled.png");
    cursor[0].set_renderer(menu_renderer);
    cursor[0].LoadFileImage("Sprites/cursor.png");
    cursor[1].set_renderer(menu_renderer);
    cursor[1].LoadFileImage("Sprites/cursor-off.png");
    fall[0].Text = "New game";
    fall[0].hover = false;
    fall[0].position.x = 70;
    fall[0].position.y = 200;
    fall[0].position.w = BUTTON_WIDTH + 50;
    fall[0].position.h = BUTTON_HEIGHT;
    fall[0].texture = setTexture(menu_font, fall[0].Text, buttonColor[0]);
    fall[1].Text = "Play again";
    fall[1].hover = false;
    fall[1].position.x = 220;
    fall[1].position.y = 300;
    fall[1].position.w = BUTTON_WIDTH + 50;
    fall[1].position.h = BUTTON_HEIGHT;
    fall[1].texture = setTexture(menu_font, fall[1].Text, buttonColor[0]);
    fall[2].Text = "Exit";
    fall[2].hover = false;
    fall[2].position.x = 400;
    fall[2].position.y = 200;
    fall[2].position.w = BUTTON_WIDTH;
    fall[2].position.h = BUTTON_HEIGHT;
    fall[2].texture = setTexture(menu_font, fall[2].Text, buttonColor[0]);
    title_fall = setTexture(menu_font, "GAME OVER", fall_color);
    title_fall_pos.x = 100;
    title_fall_pos.y = 50;
    title_fall_pos.w = 440;
    title_fall_pos.h = 150;
}
int Menu::showMenu() {
    SDL_Event e;
    int x, y;
    while (true) {
        while (SDL_PollEvent(&e) != 0) {
            switch (e.type) {
            case SDL_MOUSEMOTION:
                x = e.motion.x;
                y = e.motion.y;
                for (int i = 0; i < BUTTON_TOTAL; ++i) {
                    if (x >= menu_Button[i].position.x && x <= menu_Button[i].position.x + menu_Button[i].position.w
                        && y >= menu_Button[i].position.y && y <= menu_Button[i].position.y + menu_Button[i].position.h) {
                        if (!menu_Button[i].hover) {
                            menu_Button[i].hover = true;
                            menu_Button[i].texture = setTexture(menu_font, menu_Button[i].Text, buttonColor[1]);
                            cursor[0].render(menu_Button[i].position.x - 50, menu_Button[i].position.y + 39);
                        }
                    }
                    else if (menu_Button[i].hover) {
                        menu_Button[i].hover = false;
                        menu_Button[i].texture = setTexture(menu_font, menu_Button[i].Text, buttonColor[0]);
                        cursor[1].render(menu_Button[i].position.x - 50, menu_Button[i].position.y + 39);
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                x = e.motion.x;
                y = e.motion.y;
                for (int i = 0; i < BUTTON_TOTAL; ++i) {
                    if (x >= menu_Button[i].position.x && x <= menu_Button[i].position.x + menu_Button[i].position.w) {
                        if (y >= menu_Button[i].position.y && y <= menu_Button[i].position.y + menu_Button[i].position.h) {
                            Mix_PlayChannel(-1, mouse_click, 0);
                            SDL_Delay(200);
                            if (i == 0) return lv;
                            else if (i == 1) return help;
                            else if (i == 2) return quit;
                        }
                    }
                }
                break;
            default:
                break;
            }
        }
        SDL_RenderCopy(menu_renderer, title, NULL, &title_pos);
        for (int i = 0; i < BUTTON_TOTAL; ++i) {
            SDL_RenderCopy(menu_renderer, menu_Button[i].texture, NULL, &menu_Button[i].position);
        }
        SDL_RenderPresent(menu_renderer);
    }

    return 0;
}
int Menu::showHelp() {
    SDL_Event e;
    while (true) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
                SDL_RenderClear(menu_renderer);
                return main_menu;
            }
        }
        help_menu.render(0, 0);
        SDL_RenderPresent(menu_renderer);
    }
}
int Menu::showFall() {
    SDL_RenderClear(menu_renderer);
    SDL_Event e;
    int x, y;
    while (true) {
        while (SDL_PollEvent(&e) != 0) {
            switch (e.type) {
            case SDL_MOUSEMOTION:
                x = e.motion.x;
                y = e.motion.y;
                for (int i = 0; i < 3; ++i) {
                    if (x >= fall[i].position.x && x <= fall[i].position.x + fall[i].position.w
                        && y >= fall[i].position.y && y <= fall[i].position.y + fall[i].position.h) {
                        if (!fall[i].hover) {
                            fall[i].hover = true;
                            fall[i].texture = setTexture(menu_font, fall[i].Text, buttonColor[1]);
                            cursor[0].render(fall[i].position.x - 50, fall[i].position.y + 39);
                        }
                    }
                    else if (fall[i].hover) {
                        fall[i].hover = false;
                        fall[i].texture = setTexture(menu_font, fall[i].Text, buttonColor[0]);
                        cursor[1].render(fall[i].position.x - 50, fall[i].position.y + 39);
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                x = e.motion.x;
                y = e.motion.y;
                for (int i = 0; i < 3; ++i) {
                    if (x >= fall[i].position.x && x <= fall[i].position.x + fall[i].position.w) {
                        if (y >= fall[i].position.y && y <= fall[i].position.y + fall[i].position.h) {
                            Mix_PlayChannel(-1, mouse_click, 0);
                            SDL_Delay(200);
                            if (i == 0) {
                                lv = 1;
                                SDL_RenderClear(menu_renderer);
                                return 0;
                            }
                            else if (i == 1) return lv;
                            else if (i == 2) return quit;
                        }
                    }
                }
                break;
            default:
                break;
            }
        }
        SDL_RenderCopy(menu_renderer, title_fall, NULL, &title_fall_pos);
        for (int i = 0; i < BUTTON_TOTAL; ++i) {
            SDL_RenderCopy(menu_renderer, fall[i].texture, NULL, &fall[i].position);
        }
        SDL_RenderPresent(menu_renderer);
    }

    return 0;
}
