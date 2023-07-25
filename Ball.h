#pragma once

#include "Movable.h"

class Ball : public Movable
{
public:
	Ball();

	// Constructor with file path: initializes variables, tries to load drawable from given file path
	Ball(std::string filePath);

	virtual void move(double timeStep) override;

	// Takes key press
	void handleInput(std::string input) override;

	// Overrides to enable call to method for colliding side detection
	bool isCollidingWith(Collideable* object) override;

private:
	// Colliding side detection method
	void checkCollisionSide(Collideable* object);

	// internal value to avoid multiple collision methods being called multiple times during the same collision
	bool _hasCollided;

	double _centerOffset = 0.5;
};

