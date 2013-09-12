#pragma once

#include "utils\utils.h"

class Direction
{
public:
	Direction(int value = -1);
	Direction(String name);

	bool operator==(const Direction& d) const;
	bool operator!=(const Direction& d) const;
	bool isNull() const;
	String toString() const;
	static String valueOf(int value);

	int changeX(int x) const;
	int changeY(int y) const;
	
	Direction inverted() const;
private:
	static DirectionMap initialise();
	static const DirectionMap Directions;

	DirectionItem dir;
};

