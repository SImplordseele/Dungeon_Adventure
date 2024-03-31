#include <SDL.h>
#include <SDL_ttf.h>
#include "Texture.h"
#include <fstream>
#include <sstream>
using std::ifstream;
using std::stringstream;
class OpeningScreen {
public:
    OpeningScreen(int w, int h, SDL_Renderer* renderer, TTF_Font* font);
    ~OpeningScreen();
    void SetColor(Uint8 r, Uint8 g, Uint8 b);
    void SetTextPath(string path);
    string ReadFile();
    void RenderText();
private:
    SDL_Renderer* renderer = NULL;
    TTF_Font* font = NULL;
    int width;
    int height;
    Texture texture;
    SDL_Color color;
    string src = "NULL";
};

