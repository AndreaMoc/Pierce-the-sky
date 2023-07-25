#pragma once
#include <SDL_ttf.h>
#include <SDL_mixer.h>

// Globally used parameters

// Screen dimension constants
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

// The window we'll be rendering to
extern struct SDL_Window* globalWindow;

// The window renderer
extern struct SDL_Renderer* globalRenderer;

// Globally used font
extern TTF_Font* globalFont;

// The music that will be globally played
extern Mix_Music* globalMusic;