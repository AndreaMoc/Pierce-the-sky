#include "Position2D.h"

Position2D::Position2D() {
	_x = 0.0;
	_y = 0.0;
}

Position2D::Position2D(double x, double y) {
	_x = x;
	_y = y;
}

// Returns _x
double Position2D::getX()
{
	return _x;
}
// Returns _y
double Position2D::getY() { return _y; }

// Sets _x equal to x
void Position2D::setX(double x) { _x = x; }
// Sets _y equal to y
void Position2D::setY(double y) { _y = y; }