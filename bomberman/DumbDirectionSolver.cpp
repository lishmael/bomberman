#include "DumbDirectionSolver.h"


DumbDirectionSolver::DumbDirectionSolver(Dice* d) {
	dice = d;
}

String DumbDirectionSolver::get(Board b) {
	board = b;
	Point bomberman = board.getBomberman();

    bool nearDestroyWall = board.isNear(bomberman.getX(), bomberman.getY(), Element(L"DESTROY_WALL"));
    bool nearBomberman = board.isNear(bomberman.getX(), bomberman.getY(), Element(L"OTHER_BOMBERMAN"));
    bool nearMeatchopper = board.isNear(bomberman.getX(), bomberman.getY(), Element(L"MEAT_CHOPPER"));
    bool bombNotDropped = !board.isAt(bomberman.getX(), bomberman.getY(), Element(L"BOMB_BOMBERMAN"));

	bomb.setNull(true);
    if ((nearDestroyWall || nearBomberman || nearMeatchopper) && bombNotDropped) {
        bomb = bomberman;
		bomb.setNull(false);
    }

    direction = tryToMove(bomberman);

    return mergeCommands(bomb, direction);
}

String DumbDirectionSolver::mergeCommands(Point bomb, Direction direction) const {
	if (direction == Direction(L"STOP")) {
		bomb.setNull(true);
	}
	StringStream ss;
	if (!bomb.isNull()) {
		ss << Direction(L"ACT").toString();
		if (direction != Direction(L"NULL")) {
			ss << L",";
		}
	}
	ss << direction.toString();
	return ss.str();
}

Direction DumbDirectionSolver::tryToMove(Point pt) {
	int count = 0;
	int newX = pt.getX();
	int newY = pt.getY();
	Direction result(L"NULL");
	bool again = false;
	do {
			result = whereICanGoFrom(pt);
			if (result.isNull()) {
				return result;
			}

			newX = result.changeX(pt.getX());
			newY = result.changeY(pt.getY());

			bool bombAtWay = (!bomb.isNull()) && (bomb == Point(newX, newY));
			bool barrierAtWay = board.isBarrierAt(newX, newY);
			auto futBla = board.getFutureBlasts();
			bool blastAtWay = (std::find(futBla.begin(), futBla.end(), Point(newX, newY)) != futBla.end());
			bool meatChopperNearWay = board.isNear(newX, newY, Element(L"MEAT_CHOPPER"));

			if (blastAtWay &&
				board.countNear(pt.getX(), pt.getY(), Element(L"SPACE")) == 1 &&
				!board.isAt(pt.getX(), pt.getY(), Element(L"BOMB_BOMBERMAN"))) {
					result = Direction(L"STOP");
					return result;
			}

			again = bombAtWay || barrierAtWay || meatChopperNearWay;

			bool deadEndAtWay = (board.countNear(newX, newY, Element(L"SPACE")) == 0 && !bomb.isNull());  
			if (deadEndAtWay) {
				bomb.setNull(true);
			}
			if (result == Direction(L"NULL")) {
				again == true;
			}
	} while (count++ < 20 && again);
	if (count >= 20) {
		result = Direction(L"ACT");
    }
	return result;
}

Direction DumbDirectionSolver::whereICanGoFrom(Point pt) {
	Direction result;
	int count = 0;
	result = Direction(Direction::valueOf(dice->next(3)));
	while (count++ < 10 &&
			(
				(result.inverted() == direction && bomb.isNull()) ||
				!board.isAt(result.changeX(pt.getX()), result.changeY(pt.getY()), Element(L"SPACE"))
			)
		   )  {
		result = Direction(Direction::valueOf(dice->next(3)));
	}
    
	if (count > 10) {
		result = Direction(L"NULL");
    }
    return result;
}