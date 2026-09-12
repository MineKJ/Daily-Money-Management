#include <iostream>
#include <string>
#include "RegisterandLogin.h"
#include "models.h"
#include "tools.h"
#include "system.h"

int main() {
	User currentUser;
	bool login = true;
	int status;
	int choice;
	std::cout << "\nWelcome to Daily Money Management System!\nPlease Register or Log In an account to access the system\n";

	while (login) {
		//Login menu
		std::cout << '\n' << std::string(30, '-') << "\n1.Register\n2.Log In\n0.Exit Program\n" << std::string(30, '-') << std::endl;   //std::string here is used for layout
		choice = integerinputfilter("Enter your choice: ");

		if (choice == -1) {
			std::cout << "\nInvalid input! Do not include alphabet!";
			continue;
		}
		if (choice == -2) {
			std::cout << "\nInput cannot be empty!";
			continue;
		}
			
		switch (choice) {
		case 1:
			registerUser();
			break;
		case 2:
			status = loginUser(currentUser);
			if (status == 0) {
				std::cout << "\nLogin successfully! Directing to management page...\n";
				clearscreen();
				managemenu();
			}
			else if (status == 3) {
				std::cout << "\nLogin Cancelled.";
				break;
			}
			else {
				std::cout << "\nLogin failed! Please try again!\n";
			}
			break;
		case 0:
			std::cout << "\nExiting the system. Bye!";
			login = false;
			break;
		default:
			std::cout << "\nWrong input! Please use 1, 2 or 0 only";
			continue;
		}
	}
	return 0;
}