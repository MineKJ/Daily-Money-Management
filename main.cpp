#include <iostream>
#include <string>
#include "RegisterandLogin.h"
#include "models.h"
#include "tools.h"

int main() {
	User currentUser;
	bool login = true;
	int status;
	int choice;
	std::cout << "\nWelcome to Daily Money Management System!\nPlease Register or Log In an account to access the system\n\n";
	while (login) {
		//Login menu
		std::cout << std::string(30, '-') << "\n1.Register\n2.Log In\n0.Exit Program\n" << std::string(30, '-') << '\n';   //std::string here is used for layout
		choice = integerinputfilter("Enter your choice: ");

		if (choice == -1) {
			std::cout << "Invalid input! Do not include alphabet!\n";
			continue;
		}
		if (choice == -2) {
			std::cout << "Input cannot be empty!\n";
			continue;
		}

		switch (choice) {
		case 1:
			registerUser();
			break;
		case 2:
			status = loginUser(currentUser);
			if (status == 0) {
				std::cout << "Login successfully! Directing to management page...\n";
			}
			else {
				std::cout << "Login failed! Please try again!";
			}
			break;
		case 0:
			std::cout << "Exiting the system. Bye!";
			return 0;
		default:
			std::cout << "Wrong input! Please use 1, 2 or 0 only";
			continue;
		}
	}
}