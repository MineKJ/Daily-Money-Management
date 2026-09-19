#include "tools.h"
#include <iostream>
#include <sstream>
#include <limits>
#include <string>
#include <cstdlib>
#include <cctype>
#include <iomanip>


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

double doubleinputfilter(const std::string& prompt) {
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
		if (input < "0"){
			return -3;
		}
		//extract the input to integer and ensure there is no extra text/alphabet behind number
		std::stringstream ss(input);
		double val;
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

std::string formatdate(const std::string& prompt) {
	std::string input;
	while (true) {
		std::cout << prompt;
		std::getline(std::cin, input);
		if (input == "99") {
			return "99";
		}

		if (input.empty()) {
			std::cout << "Empty input is not allowed.\n";
			continue;
		}
		else if (input.find(' ') != std::string::npos) {
			std::cout << "Input cannot contain space.\n";
			continue;
		}
		else if (input.length() != 8) {
			std::cout << "\nThe date must follow DDMMYYYY.\n";
			continue;
		}

		bool checkAlp = true;
		for (char c : input) {
			if (!std::isdigit(static_cast<unsigned char>(c))) {
				checkAlp = false;
				break;
			}
		}
		if (!checkAlp) {
			std::cout << "\nDate cannot contain alphabet.\n";
			continue;
		}
		//check if the day and month in accurate or not
		int day = std::stoi(input.substr(0, 2));
		int month = std::stoi(input.substr(2, 2));
		if (day < 1 || day > 31 || month < 1 || month >12) {
			std::cout << "\nDay must be in 1 to 31 and month must be in 1 to 12 only!\n";
			continue;
		}
		//add - for each position
		return input.substr(0, 2) + "-" + input.substr(2, 2) + "-" + input.substr(4, 4);
	}
}
