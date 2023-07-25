#include "Ball.h"
#include <cmath>

Ball::Ball() : Movable()
{
	_hasCollided = false;
}

Ball::Ball(std::string filePath) : Movable(filePath)
{
	_hasCollided = false;
}

void Ball::move(double timeStep)
{
	// Move the texture left or right
	_position->setX(_position->getX() + _velX * timeStep);
	positionCenter();

	// If the texture went too far to the left or right:
	// set its position to the left boundary
	if (_position->getX() < 0) {
		_position->setX(0);
		positionCenter();

		_velX = -_velX;
	}
	// set its position to the right boundary
	else if (_position->getX() > SCREEN_WIDTH - _width) {
		_position->setX(SCREEN_WIDTH - _width);
		positionCenter();

		_velX = -_velX;
	}

	// Move the texture up or down
	_position->setY(_position->getY() + _velY * timeStep);
	positionCenter();

	// If the texture went too far up or down:
	// set its position to the upper boundary
	if (_position->getY() < 0) {
		_position->setY(0);
		positionCenter();

		_velY = -_velY;
	}
	// set its position to the lower boundary
	else if (_position->getY() > SCREEN_HEIGHT - _height) {
		_position->setY(SCREEN_HEIGHT - _height);
		positionCenter();

		_velY = -_velY;
	}
}


void Ball::handleInput(std::string input)
{
	if (input == "SPACEBAR")
	{
		_velX = -100;
		_velY = -200;
	}
}

bool Ball::isCollidingWith(Collideable* object)
{
	// returns false if either one of the two Collideables is not enabled
	if (_collisionEnabled == false || object->isCollisionEnabled() == false) return false;

	// checks for overlap on the X axis
	bool collisionX = this->getPosition()->getX() + _width >= object->getPosition()->getX() &&
		this->getPosition()->getX() <= object->getPosition()->getX() + object->getWidth();


	// checks for overlap on the Y axis
	bool collisionY = this->getPosition()->getY() + _height >= object->getPosition()->getY() &&
		this->getPosition()->getY() <= object->getPosition()->getY() + object->getHeight();

	// returns true only if there is an overlap on both axes, hence the two objects are colliding
	if (collisionX && collisionY)
	{
		if (!_hasCollided)
		{
			_hasCollided = true;
			checkCollisionSide(object);
		}
	}

	// TENTATIVE TO AVOID MULTIPLE COLLISIONS WITH THE SAME OBJECT; CURRENTLY NOT WORKING WITH PADDLE
	// 
	// re-enables '_hasCollided = false' only after the ball has moved away from the colliding space
	// checks for overlap on the X axis
	bool isDistantX = _position->getX() + _width <= object->getPosition()->getX() ||
		_position->getX() >= object->getPosition()->getX() + object->getWidth();

	// checks for overlap on the Y axis
	bool isDistantY = _position->getY() + _height <= object->getPosition()->getY() ||
		_position->getY() >= object->getPosition()->getY() + object->getHeight();

	if (isDistantX && isDistantY)
	{
		_hasCollided = false;
	}

	return collisionX && collisionY;
}

// Invoke only after collision; private method
void Ball::checkCollisionSide(Collideable* object)
{
	double centerDistanceY = std::abs(_center->getY() - object->getCenter()->getY());
	double centerDistanceX = std::abs(_center->getX() - object->getCenter()->getX());

	double heights = (_height / 2) + (object->getHeight() / 2);
	double widths = (_width / 2) + (object->getWidth() / 2);

	if (centerDistanceY + _centerOffset < heights)
	{
		_velX = -_velX;
	}
	else if (centerDistanceX + _centerOffset < widths)
	{
		_velY = -_velY;
	}
}
