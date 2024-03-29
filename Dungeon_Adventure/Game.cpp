#include <SDL.h>
#include <SDL_image.h>
#include "Menu.h"
#include "OpeningScreen.h"
#include "Level.h"
#include <string.h>
#include "EndingScreen.h"
const string Help_document = "Documents/Help.txt";
const string Level1_Map = "Maps/level_1_map.map";
const string Tilesprite = "Sprites/tile_sprite_sheet.png";
const string PlayerSprite = "Sprites/link_sprite_sheet.png";
const string OpenDoc = "Documents/Introduction_Text.txt";
const string fontsrc = "Fonts/font.ttf";
const string Level2_Map = "Maps/level_2_map.map";
const string Level3_Map = "Maps/level_3_map.map";
const string Level4_Map = "Maps/level_4_map.map";
const string Level5_Map = "Maps/level_5_map.map";
SDL_Window* g_window = NULL;
SDL_Renderer* g_renderer = NULL;
SDL_Renderer* open_renderer = NULL;
TTF_Font* g_font = NULL;
Texture g_texture;
string Help(string pathsrc) {
	ifstream open(pathsrc);
	if (open.fail()) {
		return "Can not open document\n";
	}
	stringstream txt;
	txt << open.rdbuf();
	return txt.str();
}
int lv = 1;
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
				SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					cout << "SDL_image could not initialize! SDL_image Error: %s\n" << IMG_GetError();
					success = false;
				}
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
					cout << "SDL_audio could not initialize! SDL_image Error: %s\n" << Mix_GetError();
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
	OpeningScreen screen(SCREEN_WIDTH, SCREEN_HEIGHT, g_window, g_renderer, g_font);
	screen.SetColor(0, 0, 0);
	screen.SetTextPath(OpenDoc);
	Player player(PlayerSprite, 0, 0, 1, 1, g_renderer);
	player.objectTexture.set_renderer(g_renderer);
	player.setClip(0, 96, Player_sprite_width, Player_sprite_height);
	Map Level1Map(286, Level1_Map, Tilesprite, g_renderer);
	Level1Map.setMapSize(22, 13);
	Level Level1(SCREEN_WIDTH, SCREEN_HEIGHT, g_window, g_renderer, &player);
	Level1.SetLevel(22, 13);
	Map Level2Map(286, Level2_Map, Tilesprite, g_renderer);
	Level2Map.setMapSize(22, 13);
	Level Level2(SCREEN_WIDTH, SCREEN_HEIGHT, g_window, g_renderer, &player);
	Level2.SetLevel(22, 13);
	Map Level3Map(345, Level3_Map, Tilesprite, g_renderer);
	Level3Map.setMapSize(23, 15);
	Level Level3(SCREEN_WIDTH, SCREEN_HEIGHT, g_window, g_renderer, &player);
	Level3.SetLevel(23, 15);
	Map Level4Map(504, Level4_Map, Tilesprite, g_renderer);
	Level4Map.setMapSize(28, 18);
	Level Level4(SCREEN_WIDTH, SCREEN_HEIGHT, g_window, g_renderer, &player);
	Level4.SetLevel(28, 18);
	Map Level5Map(640, Level5_Map, Tilesprite, g_renderer);
	Level5Map.setMapSize(32, 20);
	Level Level5(SCREEN_WIDTH, SCREEN_HEIGHT, g_window, g_renderer, &player);
	Level5.SetLevel(32, 20);
	EndingScreen Escreen(g_renderer, &player, g_font);
	Escreen.setup();
	Mix_Music* menu_music;
	menu_music = Mix_LoadMUS("Sound/menu.mp3");
	Mix_Music* ending_music;
	ending_music = Mix_LoadMUS("Sound/ending.mp3");
	bool check = false;
	bool running = true;
	int curr_screen = main_menu;
	while (running) {
		switch (curr_screen) {
		case main_menu:
			check = false;
			Mix_PlayMusic(menu_music, -1);
			Mix_VolumeMusic(50);
			curr_screen = startMenu.showMenu();
			break;
		case lv1:
			if (Mix_PlayingMusic()) {
				Mix_HaltMusic();
			}
			SDL_Delay(500);
			if (!check) {
				check = true;
				screen.RenderText();
			}
			player.SetPlayerPos(96, 960);
			Level1.LoadLevel(&Level1Map);
			curr_screen = Level1.PlayLevel();
			break;
		case lv2:
			SDL_Delay(300);
			player.SetPlayerPos(480, 192);
			Level2.LoadLevel(&Level2Map);
			curr_screen = Level2.PlayLevel();
			break;
		case lv3:
			SDL_Delay(300);
			player.SetPlayerPos(864, 576);
			Level3.LoadLevel(&Level3Map);
			curr_screen = Level3.PlayLevel();
			break;
		case lv4:
			SDL_Delay(300);
			player.SetPlayerPos(480, 768);
			Level4.LoadLevel(&Level4Map);
			curr_screen = Level4.PlayLevel();
			break;
		case lv5:
			SDL_Delay(300);
			player.SetPlayerPos(1152, 960);
			Level5.LoadLevel(&Level5Map);
			curr_screen = Level5.PlayLevel();
			break;
		case 6:
			if (Mix_PlayingMusic()) {
				Mix_HaltMusic();
			}
			Mix_PlayMusic(ending_music, -1);
			Mix_VolumeMusic(50);
			curr_screen = Escreen.play();
			break;
		case help:
			SDL_Delay(200);
			curr_screen = startMenu.showHelp();
			break;
		case quit:
			running = false;
			break;
		case falling:
			curr_screen = startMenu.showFall();
			break;
		default:
			break;
		}
	}
	cout << "END GAME\n";
	close();
	return 0;
}