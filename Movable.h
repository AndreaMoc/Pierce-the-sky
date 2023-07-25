#pragma once

#include "Collideable.h"
#include "Globals.h"

class Movable : public Collideable
{
public:
	Movable();

	// Constructor with file path: initializes variables, tries to load drawable from given file path
	Movable(std::string filePath);

	// Moves the object
	virtual void move(double timeStep);

	double getVelocityX();
	double getVelocityY();

	void setVelocityX(double velX);
	void setVelocityY(double velY);

	virtual void handleInput(std::string input) = 0;

protected:
	double _velX, _velY;
};

