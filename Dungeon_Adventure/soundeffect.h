#include <SDL_mixer.h>
class Sound {
public:
	Sound();
	~Sound();
	void knock_sound();
	void pick_sound();
	void open_sound();
	void walk_sound();
	bool isplayed();
private:
	Mix_Chunk* footstep = NULL;
	Mix_Chunk* pick_item = NULL;
	Mix_Chunk* door_open_sound = NULL;
	Mix_Chunk* door_knock_sound = NULL;
};