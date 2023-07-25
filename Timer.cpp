#include "Timer.h"

Timer::Timer() {
    _startTicks = 0;
    _pausedTicks = 0;

    _isPaused = false;
    _isStarted = false;
}

void Timer::start() {
    _isStarted = true;
    _isPaused = false;

    // Get the current clock time
    _startTicks = SDL_GetTicks();
    _pausedTicks = 0;
}

void Timer::stop() {
    _isStarted = false;
    _isPaused = false;

    // Clear tick variables
    _startTicks = 0;
    _pausedTicks = 0;
}

void Timer::pause() {
    if (_isStarted && !_isPaused) {
        _isPaused = true;

        // Calculate the paused ticks
        _pausedTicks = SDL_GetTicks() - _startTicks;
        _startTicks = 0;
    }
}

void Timer::resume() {
    if (_isStarted && _isPaused) {
        _isPaused = false;

        // Reset the starting ticks
        _startTicks = SDL_GetTicks() - _pausedTicks;

        // Reset the paused ticks
        _pausedTicks = 0;
    }
}

Uint32 Timer::getTicks() {
    // The actual timer time
    Uint32 time = 0;

    if (_isStarted) {
        if (_isPaused) {
            // Return the number of ticks when the timer was paused
            time = _pausedTicks;
        }
        else {
            // Return the current time minus the start time
            time = SDL_GetTicks() - _startTicks;
        }
    }

    return time;
}

bool Timer::isStarted() {
    // Timer is running and paused or unpaused
    return _isStarted;
}

bool Timer::isPaused() {
    // Timer is running and paused
    return _isPaused && _isStarted;
}
