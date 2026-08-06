#include <iostream>
#include <string>
#include "RegisterandLogin.h"
#include "models.h"

void main() {
	User currentUser;
	bool login = true;
	int status;
	int choice;
	while (login) {
		//Login menu
		std::cout << "\nWelcome to Daily Money Management System!\nPlease Register or Log In an account to access the system\n\n";
		std::cout << std::string(30, '-') << "\n1.Register\n2.Log In\n0.Exit Program\n" << std::string(30, '-');   //std::string here is used for layout
		std::cout  << "\nEnter your choice: ";
		std::cin >> choice;
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
			login = false;
			std::cout << "Exiting the system. Bye!";
			break;
		default:
			std::cout << "Wrong input! Please use 1, 2 or 0 only";
			return;
		}
	}
}