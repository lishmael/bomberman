#include <iostream>

#include "utils/RandomDice.h"
#include "DumbDirectionSolver.h"
#include "WebClient.h"

int main(int argc, char** argv) {
	int EXITCODE = 0;

	RandomDice* rd = new RandomDice();
	DumbDirectionSolver* dds = new DumbDirectionSolver(rd);

	WebClient wcl(dds);
	try {
		wcl.run("ws://tetrisj.jvmhost.net:12270/codenjoy-contest/ws", "lishmael");
	} catch (const std::exception& ex) {
		std::cout << "Exception happened: " << ex.what() << std::endl;
		EXITCODE = 1;
	} catch (const std::invalid_argument& iarex) {
		std::cout << "Exception happened: " << iarex.what() << std::endl;
		EXITCODE = 2;
	} catch (websocketpp::lib::error_code e) {
		std::cout << e.message() << std::endl;
	} catch (...) {
		std::cout << "Something's definitely not right..." << std::endl;
		EXITCODE = 3;
	}
	std::cout << "Done";
	std::cin.get();

	delete dds;
	delete rd;

	return EXITCODE;
}