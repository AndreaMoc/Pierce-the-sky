#pragma once

#include <SDL.h>

class Timer {
public:
	Timer();
	~Timer() = default;

	// The various clock actions
	void start();
	void stop();
	void pause();
	void resume();

	// Gets the timer's time
	Uint32 getTicks();

	// Checks if timer is started
	bool isStarted();
	// Checks if timer is paused and has already started
	bool isPaused();

private:
	// The clock time when the timer started
	Uint32 _startTicks;

	// The ticks stored when the timer was paused
	Uint32 _pausedTicks;

	// The timer status
	bool _isPaused;
	bool _isStarted;
};

