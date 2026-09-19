#include <iostream>
#include <fstream>
#include <cstdlib>
#include "models.h"
#include "RegisterandLogin.h"
#include "tools.h"

void registerUser() {
	bool registration = false;
	User newuser;
	//username
	
	while (true){
		bool checkname = false;
		newuser.username = stringinputfilter("Create a account username (Enter 99 to cancel register): ");
		if (newuser.username == "99") {
			std::cout << "\nRegistration cancel.";
			clearscreen();
			return;
		}

		std::ifstream inFile("user.txt");
		std::string fileUser, filePass;
		while (inFile >> fileUser >> filePass) {
			std::cout << "\nCheckName: Comparing " << newuser.username << " with " << fileUser;
			if (newuser.username == fileUser) {
				checkname = true;
				break;
			}
		}
		inFile.close();

		if (checkname) {
			std::cout << "\nUsername has been used. Please type another username.\n";
			continue;
		}
		break;
	}

	//password
	newuser.password = stringinputfilter("Create Password (Enter 99 to cancel): ");
	registration = true;
	if (newuser.password == "99") {
		std::cout << "\nRegistration cancel.";
		clearscreen();
		return;
	}

	if (registration) {
		std::ofstream outfile("user.txt", std::ios::app);
		outfile << newuser.username << " " << newuser.password << std::endl;
		outfile.close();
		std::cout << "\nRegister successfully! Please login.\n";
		clearscreen();
	}
	else {
		std::cout << "\nRegister unsuccessful. Please try again.\n";
		clearscreen();
	}
}

int loginUser(User& currentUser) {
	std::string inputUser, inputPass;
	inputUser = stringinputfilter("Enter your username (Enter 99 to cancel login): ");

	if (inputUser == "99") {
		return 2;
	}

	inputPass = stringinputfilter("Enter password (Enter 99 to cancel): ");

	if (inputPass == "99") {
		return 2;
	}

	std::ifstream inFile("user.txt");
	std::string fileUser, filePass;

	while (inFile >> fileUser >> filePass) {
		if (inputUser == fileUser && inputPass == filePass) {
			currentUser.username = inputUser;
			currentUser.password = inputPass;
			return 0;
		}
	}
	inFile.close();
	return 1;
}

