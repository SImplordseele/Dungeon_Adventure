#include "OpeningScreen.h"
OpeningScreen::OpeningScreen(int w, int h, SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font) {
    height = h;
    width = w;
    this->window = window;
    this->renderer = renderer;
    this->font = font;
    texture.set_font(font);
    texture.set_renderer(renderer);
}
OpeningScreen::~OpeningScreen() {
    window = NULL;
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
    if (in.fail()) {
        return "Can not open file\n";
    }
    stringstream txt;
    txt << in.rdbuf();
    return txt.str();
}
void OpeningScreen::RenderText() {
    SDL_RenderClear(renderer);
    string text = ReadFile();
    texture.LoadTextImage(text, color);
    texture.render((width - texture.get_width()) / 2, (height - texture.get_width()) / 2);
    SDL_RenderPresent(renderer);
    SDL_Event e;
    while (true) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
                return;
            }
        }

    }
}
