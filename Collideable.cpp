#include "Collideable.h"
#include "Position2D.h"

Collideable::Collideable() : Drawable()
{
	_collisionEnabled = true;
	_center = new Position2D(_position->getX() + _width / 2, _position->getY() + _height / 2);
}

Collideable::Collideable(std::string filePath) : Drawable(filePath)
{
	_collisionEnabled = true;
	_center = new Position2D(_position->getX() + _width / 2, _position->getY() + _height / 2);
}

bool Collideable::isCollidingWith(Collideable* object)
{
	// returns false if either one of the two Collideables is not enabled
	if (!_collisionEnabled || !object->isCollisionEnabled()) return false;

	// checks for overlap on the X axis
	bool collisionX = (_position->getX() + _width >= object->getPosition()->getX()) &&
		(_position->getX() <= object->getPosition()->getX() + object->getWidth());

	// checks for overlap on the Y axis
	bool collisionY = (_position->getY() + _height >= object->getPosition()->getY()) &&
		(_position->getY() <= object->getPosition()->getY() + object->getHeight());

	// returns true only if there is an overlap on both axes, hence the two objects are colliding
	return collisionX && collisionY;
}

void Collideable::setPosition(Position2D* position)
{
	_center->setX(position->getX() + _width / 2);
	_center->setY(position->getY() + _height / 2);

	Actor::setPosition(position->getX(), position->getY());
}

void Collideable::setPosition(double x, double y)
{
	_center->setX(x + _width / 2);
	_center->setY(y + _height / 2);

	Actor::setPosition(x, y);
}

void Collideable::setWidth(double width)
{
	_center->setX(_position->getX() + width / 2);

	Actor::setWidth(width);
}

void Collideable::setHeight(double height)
{
	_center->setY(_position->getY() + height / 2);

	Actor::setHeight(height);
}

bool Collideable::isCollisionEnabled()
{
	return _collisionEnabled;
}

void Collideable::setCollisionEnabled(bool enabled)
{
	_collisionEnabled = enabled;
}

void Collideable::positionCenter()
{
	_center->setX(_position->getX() + _width / 2);
	_center->setY(_position->getY() + _height / 2);
}