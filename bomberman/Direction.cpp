#include "Direction.h"


Direction::Direction(int value) {
	auto i = Directions.find(valueOf(value));
	if (i == Directions.end()) {
		throw std::invalid_argument("Direction::Direction(int value): No direction for " + value);
	}
	dir = *i;
}

Direction::Direction(String name) {
	auto i = Directions.find(name);
	if (i == Directions.end()) {
		throw std::invalid_argument("Direction::Direction(String name): No direction for such name ");
	}
	dir = *i;
}

bool Direction::operator==(const Direction& d) const {
	return d.dir == dir;
}

bool Direction::operator!=(const Direction& d) const {
	return !operator==(d);
}

bool Direction::isNull() const {
	return dir.first == L"NULL";
}

String Direction::toString() const {
	StringStream ss;
	ss <<  (isNull() ? L"" : dir.first);
	return ss.str();
}

String Direction::valueOf(int value) {
	for (auto i : Directions) {
		if (std::get<0>(i.second) == value) return i.first;
	}
	throw std::invalid_argument("Direction::valueOf(int value): No direction for " + value);
}

int Direction::changeX(int x) const {
	return x + std::get<1>(dir.second);
}

int Direction::changeY(int y) const {
	return y + std::get<2>(dir.second);
}

Direction Direction::inverted() const {
	if (dir.first == L"UP") return Direction(L"DOWN");
	if (dir.first == L"DOWN") return Direction(L"UP");
	if (dir.first == L"LEFT") return Direction(L"RIGHT");
	if (dir.first == L"RIGHT") return Direction(L"LEFT");
	return Direction(L"STOP");
}


DirectionMap Direction::initialise() {
	DirectionMap mapOfDirections;
	mapOfDirections[L"NULL"] = DirectionVector(-1, 0, 0);

	// direction of Bomberman
	mapOfDirections[L"UP"] = DirectionVector(2, 0, -1);
	mapOfDirections[L"DOWN"] = DirectionVector(3, 0, 1);
	mapOfDirections[L"LEFT"] = DirectionVector(0, -1, 0);
	mapOfDirections[L"RIGHT"] = DirectionVector(1, 1, 0);

	// drop a bomb
	mapOfDirections[L"ACT"] = DirectionVector(4, 0, 0);

	// stop the Bomberman
	mapOfDirections[L"STOP"] = DirectionVector(5, 0, 0);
	return mapOfDirections;
}

const DirectionMap Direction::Directions = Direction::initialise();