#include "soundeffect.h"
Sound::Sound() {
	footstep = Mix_LoadWAV("Sound/walk.wav");
	pick_item = Mix_LoadWAV("Sound/pick.wav");
	door_open_sound = Mix_LoadWAV("Sound/open.wav");
	door_knock_sound = Mix_LoadWAV("Sound/knock.wav");
	death_sound_effect = Mix_LoadMUS("Sound/death.mp3");
	Mix_VolumeChunk(footstep, 40);
	Mix_VolumeChunk(pick_item, MIX_MAX_VOLUME);
}
Sound::~Sound() {
	if (footstep != NULL) {
		Mix_FreeChunk(footstep);
	}
	if (pick_item != NULL) {
		Mix_FreeChunk(pick_item);
	}
	if (door_open_sound != NULL) {
		Mix_FreeChunk(door_open_sound);
	}
	if (door_knock_sound != NULL) {
		Mix_FreeChunk(door_knock_sound);
	}
}
void Sound::knock_sound() {
	Mix_PlayChannel(-1, door_knock_sound, 0);
}
void Sound::pick_sound() {
	if (Mix_Playing(-1)) {
		Mix_HaltChannel(-1);
	}
	Mix_PlayChannel(-1, pick_item, 0);
}
void Sound::open_sound() {
	Mix_PlayChannel(-1, door_open_sound, 0);
}
void Sound::walk_sound() {
	Mix_PlayChannel(-1, footstep, 0);
}
void Sound::death_sound() {
	if (Mix_PlayingMusic()) {
		Mix_HaltMusic();
	}
	Mix_PlayMusic(death_sound_effect, 1);
	Mix_VolumeMusic(50);
}