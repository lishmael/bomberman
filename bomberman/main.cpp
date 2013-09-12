#include <iostream>

#include "Test.h"
#include "utils\RandomDice.h"
#include "WebClient.h"

int main(int argc, char** argv) {
	RandomDice* rd = new RandomDice();
	DumbDirectionSolver* dds = new DumbDirectionSolver(rd);
	Test t(dds, rd);
	WebClient wcl(dds);
	try {
		wcl.run("ws://tetrisj.jvmhost.net:12270/codenjoy-contest/ws", "lishmael");
		wcl.get();
	} catch (std::exception& ex) {
		std::cerr << "Exception happened: " << ex.what() << std::endl;
		std::cin.get();
	} catch (std::invalid_argument& iarex) {
		std::cerr << "Exception happened: " << iarex.what() << std::endl;
		std::cin.get();
	} catch (...) {
		std::cerr << "Something's definitely not right..." << std::endl;
		std::cin.get();
	}
	delete dds;
	delete rd;
	return 0;
}