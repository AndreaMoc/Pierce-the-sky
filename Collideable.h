#pragma once

#include"Drawable.h"

class Collideable : public Drawable
{
public:
	Collideable();

	// Constructor with file path: initializes variables, tries to load drawable from given file path
	Collideable(std::string filePath);

	// AABB collision algorithm
	virtual bool isCollidingWith(Collideable* object);
	
	// Overriding methods to include _center
	void setPosition(Position2D* position) override;
	void setPosition(double x, double y) override;
	void setWidth(double width) override;
	void setHeight(double height) override;

	bool isCollisionEnabled();
	void setCollisionEnabled(bool enabled);

	void positionCenter();
	Position2D* getCenter() { return _center; }
	void setCenter(Position2D* center) { _center = center; }

protected:
	bool _collisionEnabled;
	Position2D* _center;
};

