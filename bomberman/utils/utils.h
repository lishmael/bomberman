#pragma once

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <list>
#include <map>
#include <tuple>
#include <memory>
#include <sstream>
#include <string>
#include <stdexcept>

extern class Point;
extern class Direction;
extern class Element;
extern class DirectionSolver;
extern class Dice;

typedef std::wstring String;
typedef std::wstringstream StringStream;
typedef std::list<Point> PointList;
typedef std::map<String, wchar_t> ElementMap;
typedef std::pair<String, wchar_t> ElementItem;

typedef std::tuple<int, int, int> DirectionVector; // Direction vector: value, dx, dy
typedef std::pair<String, DirectionVector> DirectionItem;
typedef std::map<String, DirectionVector> DirectionMap;