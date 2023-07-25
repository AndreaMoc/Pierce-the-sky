#include "Block.h"

Block::Block() : Collideable()
{
	_value = 0;
}

Block::Block(std::string filePath) : Collideable(filePath)
{
	_value = 0;
}