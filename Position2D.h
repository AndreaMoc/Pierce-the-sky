#pragma once

/* coordinates(x, y) expressed as values of type 'double'
* 
*/

class Position2D {

public:
	Position2D();
	Position2D(double x, double y);
	~Position2D() = default;

	// Returns _x
	double getX();
	// Returns _y
	double getY();

	// Sets _x equal to x
	void setX(double x);
	// Sets _y equal to y
	void setY(double y);

private:
	double _x;
	double _y;
};