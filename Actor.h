#pragma once

#include "Position2D.h"

class Actor
{
public:
	Actor();
	~Actor() = default;

	Position2D* getPosition();
	double getWidth();
	double getHeight();

	virtual void setPosition(Position2D* position);
	virtual void setPosition(double x, double y);
	virtual void setWidth(double width);
	virtual void setHeight(double height);

protected:
	// (x,y) position, width and height
	Position2D* _position;
	double _width;
	double _height;
};

