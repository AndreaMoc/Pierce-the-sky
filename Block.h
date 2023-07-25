#pragma once

#include "Collideable.h"
#include <string>

class Block : public Collideable
{
public:
	Block();

	// Constructor with file path: initializes variables, tries to load drawable from given file path
	Block(std::string filePath);

	int getValue() { return _value; }
	void setValue(int value) { _value = value; }
private:
	int _value;
};

