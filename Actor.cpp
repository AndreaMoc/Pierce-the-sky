#include "Actor.h"

Actor::Actor()
{
	_position = new Position2D(0, 0);
	_width = 0;
	_height = 0;
}

Position2D* Actor::getPosition() { return _position; }

double Actor::getWidth() {	return _width; }

double Actor::getHeight() { return _height; }

void Actor::setPosition(Position2D* position) {	_position = position; }

void Actor::setPosition(double x, double y)
{
	_position->setX(x);
	_position->setY(y);
}

void Actor::setWidth(double width) { _width = width; }

void Actor::setHeight(double height) { _height = height; }
