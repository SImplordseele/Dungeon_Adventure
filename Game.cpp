#include <SDL.h>
#include <SDL_image.h>
#include "Menu.h"
#include "OpeningScreen.h"
#include "Level.h"
#include <string.h>
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const string Help_document = "Documents/Help.txt";
const string Level1_Map = "Maps/level_1_map.map";
const string Tilesprite = "Sprites/tile_sprite_sheet.png";
const string PlayerSprite = "Sprites/link_sprite_sheet.png";
const string OpenDoc = "Documents/Introduction_Text.txt";
const string fontsrc = "Fonts/Times_New_Roman.ttf";
SDL_Window* g_window = NULL;
SDL_Renderer* g_renderer = NULL;
TTF_Font* g_font = NULL;
string Help(string pathsrc) {
	ifstream open(pathsrc);
	if (open.fail()) {
		return "Can not open document\n";
	}
	stringstream txt;
	txt << open.rdbuf();
	return txt.str();
}
bool Init() {
	//Initialization flag
	bool success = true;
	//Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "SDL could not initialize! SDL Error: %s\n" << SDL_GetError();
		success = false;
	}
	else if (TTF_Init() == -1) {
		cout << "SDL_ttf could not initialize! SDL_ttf Error: %s\n" << TTF_GetError();
		success = false;
	}
	else {
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			cout << "Warning: Linear texture filtering not enabled!\n";
		}
		//Create window
		g_window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (g_window == NULL) {
			cout << "Window could not be created! SDL Error: %s\n" << SDL_GetError();
			success = false;
		}
		else {
			g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (g_renderer == NULL) {
				cout << "Renderer could not be created! SDL Error: %s\n" << SDL_GetError();
				success = false;
			}
			else {
				//Initialize renderer color
				SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					cout << "SDL_image could not initialize! SDL_image Error: %s\n" << IMG_GetError();
					success = false;
				}
			}
		}
	}
	g_font = TTF_OpenFont(fontsrc.c_str(), 24);
	return success;
}
void close() {
	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);
	TTF_CloseFont(g_font);
	g_window = NULL;
	g_renderer = NULL;
	g_font = NULL;
	TTF_Quit();
	SDL_Quit();
	IMG_Quit();
}
int main(int argc, char* argv[]) {
	if (!Init()) return -1;
	Menu startMenu(640, 480, g_window, g_renderer, g_font);
	startMenu.setupMenu();
	OpeningScreen screen(SCREEN_WIDTH, SCREEN_HEIGHT, g_window, g_renderer,g_font);
	screen.SetColor(0, 0, 0);
	screen.SetTextPath(OpenDoc);

	Player player(PlayerSprite,0,0,1,1,g_renderer);
	player.objectTexture.set_renderer(g_renderer);
	player.setClip(0, 96, Player_sprite_width, Player_sprite_height);

	Map Level1Map(286, Level1_Map, Tilesprite, g_renderer);
	Level1Map.setMapSize(22, 13);
	
	Level Level1(SCREEN_WIDTH, SCREEN_HEIGHT, g_window, g_renderer, &player);
	Level1.SetLevel(22, 13);
	Level1.LoadLevel(&Level1Map);
	player.SetPlayerPos(96, 960);

	bool running = true;
	int curr_screen = main_menu;
	while (running) {
		switch (curr_screen) {
			case main_menu:
				curr_screen = startMenu.showMenu();
				break;
			case start:
				SDL_Delay(500);
				screen.RenderText();
				curr_screen = Level1.PlayLevel();
				break;
			case help:
				cout << Help(Help_document) << "\n";
				curr_screen = main_menu;
				break;
			case Exit:
				cout << "Quit game\n";
				running = false;
				break;
			case Won:
				cout << "You won\n";
				break;
			case falling:
				cout << "You lost\n";
				running = false;
				break;
			default:
				break;
		}
	}
	cout << "END GAME\n";
	close();
	return 0;
}