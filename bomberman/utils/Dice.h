#pragma once

#include "utils.h"

class Dice {
public:
	Dice() {};
	virtual int next(int max) = 0;
};