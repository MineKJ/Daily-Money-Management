#include "tools.h"
#include <iostream>
#include <sstream>
#include <limits>
#include <string>
#include <cstdlib>


int integerinputfilter(const std::string& prompt) {
	std::cin.clear();
	std::string input;

	while (true) {
		std::cout << prompt;
		if (!std::getline(std::cin, input)) {
			return -1;
		}

		if (input.empty()) {
			return -2;
		}
		//extract the input to integer and ensure there is no extra text/alphabet behind number
		std::stringstream ss(input);
		int val;
		char extra;

		if (ss >> val && !(ss >> extra)) {
			return val;
		}
		else {
			return -1;
		}
	}
}

std::string stringinputfilter(const std::string& prompt) {
	std::cin.clear();
	std::string input;

	while (true) {
		std::cout << prompt;
		if (!std::getline(std::cin, input)) {
			return "";
		}

		if (input.empty()) {
			std::cout << "Empty input is not allowed.\n";
			continue;
		}

		if (input.find(' ') != std::string::npos) {
			std::cout << "Input cannot contain space.\n";
			continue;
		}
		return input;
	}
}

void clearscreen() {
	std::cout << "\n-> Press [Enter] to continue...";
	std::cin.get();
	system("cls");
}
