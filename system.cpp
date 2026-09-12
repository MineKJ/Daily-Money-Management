#include <iostream>
#include "system.h"
#include "tools.h"

void managemenu(){
	int choice;
	bool loggedin = true;

	while (loggedin) {
		std::cout << "=========================================\n";
		std::cout << "     Daily Money Management System\n";
		std::cout << "=========================================\n";
		std::cout << "1. Add Record\n2. Update Record\n3. Delete Record\n3. Display Record\n0. Exit\n";
		choice = integerinputfilter("Enter your choice: ");

		if (choice == 1) {
			std::cout << "Add record"; //Add new record
			continue;
		}
		else if (choice == 2) {
			std::cout << "Update record"; //update record
			continue;
		}
		else if (choice == 3) {
			std::cout << "Delete Record"; //delete record
			continue;
		}
		else if (choice == 0) { //exit
			loggedin = false;
			clearscreen();
			break;
		}
		else {
			std::cout << "\nInvalid option. Please type (0-3) only!\n";
			clearscreen();
			continue;
		}
	}
}