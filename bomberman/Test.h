#pragma once

#include "utils\utils.h"
#include "DumbDirectionSolver.h"
#include <cstdarg>
#include <iostream>

class Test
{
public:
	Test(DirectionSolver* dirs, Dice* dc) : solver(dirs), dice(dc) {
	}

	bool test() {
		StringStream ss;
		ss <<   L"☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼\n" <<     
				L"☼☺        # # ☼\n" <<
				L"☼ ☼ ☼ ☼#☼ ☼ ☼ ☼\n" <<
				L"☼##           ☼\n" <<
				L"☼ ☼ ☼#☼ ☼ ☼ ☼ ☼\n" <<
				L"☼   #    # #  ☼\n" <<
				L"☼ ☼ ☼ ☼#☼ ☼ ☼ ☼\n" <<
				L"☼             ☼\n" <<
				L"☼#☼ ☼ ☼#☼ ☼ ☼#☼\n" <<
				L"☼  #  #       ☼\n" <<
				L"☼ ☼ ☼ ☼ ☼ ☼ ☼#☼\n" <<
				L"☼ ##      #   ☼\n" <<
				L"☼ ☼ ☼ ☼ ☼ ☼ ☼#☼\n" <<
				L"☼ #   #  &    ☼\n" <<
				L"☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼";
		return runTest(ss.str(), L"RIGHT", 0);
	}

private:
	Dice* dice;
	DirectionSolver* solver;
	bool runTest(String brd, String expRes, int dirCount, ...) {
		std::list<Direction> directions;
		va_list dirs;
		va_start(dirs, dirCount);
		for (auto i = 0; i < dirCount; ++i) { 
			directions.push_back(va_arg(dirs, Direction));
		}
		va_end(dirs);
		String result = solver->get(Board(brd));
		std::wcout << "Result string: " << result << std::endl;
		if (result == expRes) return true;
		return false;
	}
};

