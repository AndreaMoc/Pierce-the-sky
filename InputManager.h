#pragma once

#include <SDL.h>
#include <string>
#include "Paddle.h"

class InputManager
{
public:
	InputManager(Movable* movableCharacter);
	~InputManager() = default;

	void getInput(SDL_Event& sdlEvent);

private:
	Movable* _movableCharacter;
};

