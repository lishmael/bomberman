#pragma once

#include "utils\utils.h"

#include "DirectionSolver.h"
#include "Direction.h"
#include "Element.h"
#include "utils\Dice.h"
#include "utils\Point.h"

class DumbDirectionSolver :	public DirectionSolver {
public:
	DumbDirectionSolver(Dice* dice);
	virtual String get(Board board);
private:
	String mergeCommands(Point bomb, Direction direction) const;
	Direction tryToMove(Point pt);
	Direction whereICanGoFrom(Point pt);

	Direction direction;
	Point bomb;
	Dice* dice;
	Board board;
};

