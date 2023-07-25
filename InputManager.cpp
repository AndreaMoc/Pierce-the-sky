#include "InputManager.h"

InputManager::InputManager(Movable* movableCharacter) {
    _movableCharacter = movableCharacter;
}

void InputManager::getInput(SDL_Event& sdlEvent) {
    std::string result = "";
    char key;
    
    // If a key was pressed
    if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.repeat == 0) {
        switch (sdlEvent.key.keysym.sym) {
            case SDLK_UP:
            case 'w':
                result = "UP";
                key = 'w';
                break;

            case SDLK_DOWN:
            case 's':
                result = "DOWN";
                key = 's';
                break;

            case SDLK_LEFT:
            case 'a':
                result = "LEFT";
                key = 'a';
                break;

            case SDLK_RIGHT:
            case 'd':
                result = "RIGHT";
                key = 'd';
                break;
        }
    }

    // If a key was released
    else if (sdlEvent.type == SDL_KEYUP && sdlEvent.key.repeat == 0) {
        switch (sdlEvent.key.keysym.sym) {
        case SDLK_UP:
        case 'w':
            result = "DOWN";
            key = 'w';
            break;

        case SDLK_DOWN:
        case 's':
            result = "UP";
            key = 's';
            break;

        case SDLK_LEFT:
        case 'a':
            result = "RIGHT";
            key = 'a';
            break;

        case SDLK_RIGHT:
        case 'd':
            result = "LEFT";
            key = 'd';
            break;
        case SDLK_SPACE:
            result = "SPACEBAR";
            break;
        }
    }

    _movableCharacter->handleInput(result);
}