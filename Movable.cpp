#include "Movable.h"

Movable::Movable() : Collideable()
{
	_velX = 0;
	_velY = 0;
}

Movable::Movable(std::string filePath) : Collideable(filePath)
{
	_velX = 0;
	_velY = 0;
}

void Movable::move(double timeStep)
{
	// Move the texture left or right
	_position->setX(_position->getX() + _velX * timeStep);
	positionCenter();

	// If the texture went too far to the left or right:
	// set its position to the left boundary
	if (_position->getX() < 0) {
		_position->setX(0);
		positionCenter();
	}
	// set its position to the right boundary
	else if (_position->getX() > SCREEN_WIDTH - _width) {
		_position->setX(SCREEN_WIDTH - _width);
		positionCenter();
	}
	
	// Move the texture up or down
	_position->setY(_position->getY() + _velY * timeStep);
	positionCenter();

	// If the texture went too far up or down:
	// set its position to the upper boundary
	if (_position->getY() < 0) {
		_position->setY(0);
		positionCenter();
	}
	// set its position to the lower boundary
	else if (_position->getY() > SCREEN_HEIGHT - _height) {
		_position->setY(SCREEN_HEIGHT - _height);
		positionCenter();
	}
}

double Movable::getVelocityX() { return _velX; }

double Movable::getVelocityY() { return _velY; }

void Movable::setVelocityX(double velX) { _velX = velX; }

void Movable::setVelocityY(double velY) { _velY = velY; }