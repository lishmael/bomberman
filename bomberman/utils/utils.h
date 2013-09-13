#ifndef UTILS_H
#define UTILS_H

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

typedef std::wstring String;
typedef std::wstringstream StringStream;
typedef std::map<String, wchar_t> ElementMap;
typedef std::pair<String, wchar_t> ElementItem;

typedef std::tuple<int, int, int> DirectionVector; // Direction vector: value, dx, dy
typedef std::pair<String, DirectionVector> DirectionItem;
typedef std::map<String, DirectionVector> DirectionMap;

#endif