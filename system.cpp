#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include "system.h"
#include "tools.h"
#include "storage.h"
#include "models.h" 

void managemenu(User& currentUser, std::vector<Record>& myRecord) {
	readUserRecord(currentUser);
	bool loggedin = true;
	while (loggedin) {
		double totalsavings = 0.0;
		double totalexpenses = 0.0;
		double totalbalance;
		std::cout << "=========================================\n";
		std::cout << "     Daily Money Management System\n";
		std::cout << "=========================================\n";
		std::cout << "1. Add Record\n2. Update Record\n3. Display Record\n0. Exit\n--------------------------\n";
		for (const auto& r : currentUser.myRecord) {
			totalsavings += r.savings;
			totalexpenses += r.expenses;
		}
		totalbalance = totalsavings - totalexpenses;
		std::cout << "Current Balance: RM " << std::fixed << std::setprecision(2) << totalbalance << "\n--------------------------\n";
		int choice = integerinputfilter("Enter your choice: ");

		if (choice == -1) {
			std::cout << "\nInvalid input! Do not include alphabet!\n";
			continue;
		}
		if (choice == -2) {
			std::cout << "\nInput cannot be empty!\n";
			continue;
		}
		if (choice == 1) {
			addrecord(currentUser, myRecord);//Add new record
			continue;
		}
		else if (choice == 2) {
			updaterecord(currentUser, myRecord); //update record
			continue;
		}
		else if (choice == 3) {
			displayrecord(currentUser, myRecord); //display all record
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

void addrecord(User& currentUser, std::vector<Record>& myRecord) {
	int choice;
	std::string nameS, nameE;
	std::string date = formatdate("Enter the date |DDMMYYYY| (Enter 0 to cancel): "); //the function is used to change the date to DDMMYYYY format

	if (date == "0") {
		std::cout << "\nAdd record cancelled.\n";
		clearscreen();
		return;
	}
	int foundindex = -1;
	for (size_t i = 0; i < currentUser.myRecord.size(); ++i) {
		if (currentUser.myRecord[i].date == date) {
			foundindex = static_cast<int>(i);
			break;
		}
	}

	if (foundindex == -1) {
		Record newrecord;
		newrecord.date = date;
		newrecord.savings = 0.0;
		newrecord.expenses = 0.0;
		currentUser.myRecord.push_back(newrecord);
		foundindex = static_cast<int>(currentUser.myRecord.size() - 1);
	}

	std::cout << "\n--------------------------\n1. Add Savings\n2. Add Expenses\n--------------------------\n";
	while (true) {
		choice = integerinputfilter("Choose an option (Enter 0 to cancel): ");
		if (choice == -1) {
			std::cout << "\nInvalid input! Do not include alphabet!\n";
			continue;
		}
		if (choice == -2) {
			std::cout << "\nInput cannot be empty!\n";
			continue;
		}
		if (choice == 0) {
			std::cout << "\nAdd record cancelled.\n";
			clearscreen();
			return;
		}
		if (choice == 1) {
			nameS = stringinputfilter("Enter the name of the savings (Enter 0 to cancel): ");
			if (nameS == "0") {
				std::cout << "\nAdded Cancelled.\n";
				clearscreen();
				return;
			}
			double validSavings = 0.0;
			while (true) {
				double inputval = doubleinputfilter("Enter the amount of the savings (Enter 0 to cancel): ");

				if (inputval == -1) {
					std::cout << "\nInvalid input! Do not include alphabet!\n";
					continue;
				}
				else if (inputval == -2) {
					std::cout << "\nInput cannot be empty!\n";
					continue;
				}
				else if (inputval == 0) {
					std::cout << "\nAdded Cancelled.\n";
					clearscreen();
					break;
				}
				else {
					validSavings = inputval;
					break;
				}
			}
			currentUser.myRecord[foundindex].nameS = nameS;
			currentUser.myRecord[foundindex].savings = validSavings;

			saveUserRecord(currentUser);	//this function can automatically save the input u just type into txt file
			std::cout << "\nSuccessfully added savings into record.\n";
			clearscreen();
		}
		else if (choice == 2) {
			//add new record here
			double validExpense = 0.0;
			nameE = stringinputfilter("Enter the name of the expense (Enter 0 to cancel): ");
			if (nameE == "0") {
				std::cout << "\nAdded Cancelled.\n";
				clearscreen();
				return;
			}
			while (true) {
				double inputval = doubleinputfilter("Enter the amount of the expense (Enter 0 to cancel): ");

				if (inputval == -1) {
					std::cout << "\nInvalid input! Do not include alphabet!\n";
					continue;
				}
				else if (inputval == -2) {
					std::cout << "\nInput cannot be empty!\n";
					continue;
				}
				else if (inputval == 0) {
					std::cout << "\nAdded Cancelled\n";
					clearscreen();
					break;
				}
				else {
					validExpense = inputval;
					break;
				}
			}
			currentUser.myRecord[foundindex].nameE = nameE;
			currentUser.myRecord[foundindex].expenses = validExpense;

			saveUserRecord(currentUser);	//this function can automatically save the input u just type into txt file
			std::cout << "\nSuccessfully added expense into record.\n";
			clearscreen();
		}
		else {
			std::cout << "\nInvalid number. Please choose option from 1 and 2 only!\n";
			clearscreen();
			break;
		}
		break;
	}
}

void updaterecord(User& currentUser, std::vector<Record>& myRecord) {
	std::string nameS, nameE;
	if (currentUser.myRecord.empty()) {
		std::cout << "\nNo record found.\n";
		return;
	}
	std::string finddate = formatdate("Enter the date to update DDMMYYYY (Enter 0 to cancel): ");

	if (finddate == "0") {
		std::cout << "\nUpdate cancelled.\n";
		clearscreen();
		return;
	}
	int foundindex = -1;
	for (size_t i = 0; i < currentUser.myRecord.size(); ++i) {
		if (currentUser.myRecord[i].date == finddate) {
			foundindex = static_cast<int>(i);
			break;
		}
	}

	std::cout << "\n--------------------------\n1. Update Savings\n2. Update Expenses\n--------------------------\n";
	int choice = integerinputfilter("Enter your choice (Enter 0 to cancel): ");
	if (choice == 0) {
		std::cout << "\nUpdate Cancelled.\n";
		clearscreen();
		return;
	}
	if (choice == 1) {
		std::cout << "\n--------------------------------------";
		std::cout << "\nCurrent Name: " << currentUser.myRecord[foundindex].nameS;
		std::cout << "\nCurrent Savings: " << currentUser.myRecord[foundindex].savings;
		std::cout << "\n--------------------------------------\n";

		nameS = stringinputfilter("Enter new name (Enter 0 to cancel): ");
		if (nameS == "0") {
			std::cout << "\nUpdate Cancelled.\n";
			clearscreen();
			return;
		}

		double validSavings = 0.0;
		while (true) {
			double inputval = doubleinputfilter("Enter new savings (Enter 0 to cancel): ");

			if (inputval == -1) {
				std::cout << "\nInvalid input! Do not include alphabet!\n";
				continue;
			}
			else if (inputval == -2) {
				std::cout << "\nInput cannot be empty!\n";
				continue;
			}
			else if (inputval == 0) {
				std::cout << "\nUpdate Cancelled\n";
				clearscreen();
				break;
			}
			else {
				validSavings = inputval;
				break;
			}
		}
		currentUser.myRecord[foundindex].nameS = nameS;
		currentUser.myRecord[foundindex].savings = validSavings;

		saveUserRecord(currentUser);
		std::cout << "\nSuccessfully updated!\n";
		clearscreen();
	}
	if (choice == 2) {
		std::cout << "\n--------------------------------------";
		std::cout << "\nCurrent Name: " << currentUser.myRecord[foundindex].nameE;
		std::cout << "\nCurrent Balance: " << currentUser.myRecord[foundindex].expenses;
		std::cout << "\n--------------------------------------\n";

		nameE = stringinputfilter("Enter new name (Enter 0 to cancel): ");
		if (nameE == "0") {
			std::cout << "\nUpdate cancelled.\n";
			clearscreen();
			return;
		}

		double validExpense = 0.0;
		while (true) {
			double inputval = doubleinputfilter("Enter new expense (Enter 0 to cancel): ");

			if (inputval == -1) {
				std::cout << "\nInvalid input! Do not include alphabet!\n";
				continue;
			}
			else if (inputval == -2) {
				std::cout << "\nInput cannot be empty!\n";
				continue;
			}
			else if (inputval == 0) {
				std::cout << "\nUpdate Cancelled\n";
				clearscreen();
				break;
			}
			else {
				validExpense = inputval;
				break;
			}
		}
		currentUser.myRecord[foundindex].nameE = nameE;
		currentUser.myRecord[foundindex].expenses = validExpense;

		saveUserRecord(currentUser);
		std::cout << "\nSuccessfully updated!\n";
		clearscreen();
	}
	else {
		std::cout << "\nInvalid choice. Please try again!\n";
		clearscreen();
		return;
	}
}

void displayrecord(User& currentUser, const std::vector<Record>& myRecord) {
	if (currentUser.myRecord.empty()) {
		std::cout << "\nNo record found.\n";
		clearscreen();
		return;
	}

	std::cout
		<< "\n- ---------- - -------------------- - -------------------- - ---------- - ---------- -"
		<< "\n|    Date    |     Savings'Name     |     Expenses'Name    |   Savings  |  Expenses  |"
		<< "\n- ---------- - -------------------- - -------------------- - ---------- - ---------- -\n";

	for (const auto& r : currentUser.myRecord) {
		std::cout << std::left << std::fixed << std::setprecision(2)
			<< "| " << std::setw(11) << r.date
			<< "| " << std::setw(21) << r.nameS
			<< "| " << std::setw(21) << r.nameE
			<< "| " << std::setw(11) << r.savings
			<< "| " << std::setw(11) << r.expenses
			<< "|" << std::endl;
	}
	std::cout << "- ---------- - -------------------- - -------------------- - ---------- - ---------- -\n";

	double totalSavings = 0.0;
	double totalExpenses = 0.0;
	double totalbalance;
	for (const auto& r : currentUser.myRecord) {
		totalSavings += r.savings;
		totalExpenses += r.expenses;
	}
	totalbalance = totalSavings - totalExpenses;
	std::cout
		<< "\n- ------------------------------ -"
		<< "\n| Total Savings   : RM " << std::setw(8) << totalSavings << "  |"
		<< "\n| Total Expenses  : RM " << std::setw(8) << totalExpenses << "  |"
		<< "\n| Current Balance : RM " << std::setw(8) << totalbalance << "  |
		<< "\n- ------------------------------ -\n";
	clearscreen();
}
