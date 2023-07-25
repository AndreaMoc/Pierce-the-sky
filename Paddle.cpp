#include "Paddle.h"

Paddle::Paddle() : Movable()
{

}

Paddle::Paddle(std::string filePath) : Movable(filePath)
{

}

void Paddle::handleInput(std::string input)
{
	if (input == "LEFT") { _velX -= _maxVelocity; }
	else if (input == "RIGHT") { _velX += _maxVelocity; }
}