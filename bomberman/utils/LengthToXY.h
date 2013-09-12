#pragma once

#include <stdexcept>

#include "Point.h"

class LengthToXY {
public:
	LengthToXY(int _boardSize = 0);
	Point getXY(int length) const;
	int getLength(int _x, int _y) const;
private:
	int boardSize;
};

