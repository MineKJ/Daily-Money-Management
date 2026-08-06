#include <iostream>
#include <fstream>
#include "models.h"
#include "RegisterandLogin.h"

void registerUser() {
	User newuser;
	//username
	std::cout << "\nCreate a account name: ";
	std::cin >> newuser.username;
	//password
	std::cout << "Create Password: ";
	std::cin >> newuser.password;

	std::ofstream outfile("user.txt", std::ios::app);
	outfile << newuser.username << " " << newuser.password;
	outfile.close();
	std::cout << "\nRegister successfully! Please login.\n\n";
}

int loginUser(User& currentUser) {
	std::string inputUser, inputPass;
	std::cout << "\nEnter your username: ";
	std::cin >> inputUser;
	std::cout << "Enter password: ";
	std::cin >> inputPass;

	std::ifstream inFile("user.txt");
	std::string fileUser, filePass;

	while (inFile >> fileUser >> filePass) {
		if (inputUser == fileUser && inputPass == filePass) {
			currentUser.username = inputUser;
			currentUser.password = inputPass;
			return 0;
		}
	}
	
	return 2;
}

