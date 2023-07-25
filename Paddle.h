#pragma once

#include "Movable.h"
#include "Ball.h"

class Paddle : public Movable
{
public:
	Paddle();

	// Constructor with file path: initializes variables, tries to load drawable from given file path
	Paddle(std::string filePath);

	// Takes key presses and adjusts the texture's velocity
	void handleInput(std::string input) override;

private:
	int _maxVelocity = 300;
};