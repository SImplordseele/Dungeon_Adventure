#include "OpeningScreen.h"
OpeningScreen::OpeningScreen(int w, int h,SDL_Renderer* renderer, TTF_Font* font) {
    height = h;
    width = w;
    this->renderer = renderer;
    this->font = font;
    texture.set_font(font);
    texture.set_renderer(renderer);
}
OpeningScreen::~OpeningScreen() {
    renderer = NULL;
    font = NULL;
}
void OpeningScreen::SetColor(Uint8 r, Uint8 g, Uint8 b) {
    color = { r, g, b };
}
void OpeningScreen::SetTextPath(string path) {
    src = path;
}
string OpeningScreen::ReadFile() {
    ifstream in;
    in.open(src);
    stringstream txt;
    txt << in.rdbuf();
    return txt.str();
}
void OpeningScreen::RenderText() {
    SDL_SetRenderDrawColor(renderer,255, 255, 255, 255);
    SDL_RenderClear(renderer);
    string text = ReadFile();
    texture.LoadTextImage(text, color);
    texture.render((width - texture.get_width()) / 2, (height - texture.get_width()) / 2 + 80);
    SDL_RenderPresent(renderer);
    SDL_Event e;
    while (true) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
                SDL_SetRenderDrawColor(renderer, 0, 0,0, 255);
                return;
            }
        }

    }
}
