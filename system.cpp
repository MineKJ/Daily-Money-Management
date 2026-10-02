#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
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
		std::cout << "1. Add Record\n2. Update Record\n3. Display Record\n4. Delete Record\n0. Exit\n----------------------------------------\n";
		for (const auto& r : currentUser.myRecord) {
			totalsavings += r.savings;
			totalexpenses += r.expenses;
		}
		totalbalance = totalsavings - totalexpenses;
		std::cout << "Current Balance: RM " << std::fixed << std::setprecision(2) << totalbalance << "\n----------------------------------------\n";
		int choice = integerinputfilter("Enter your choice (0-4): ");

		if (choice == -1) {
			std::cout << "\nInvalid input! Do not include alphabet or symbols!\n";
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
		else if (choice == 4) {
			deleterecord(currentUser, myRecord); //delete record
			continue;
		}
		else if (choice == 0) { //exit
			loggedin = false;
			clearscreen();
			break;
		}
		else {
			std::cout << "\nInvalid option. Please type (0-4) only!\n";
			clearscreen();
			continue;
		}
	}
}

void addrecord(User& currentUser, std::vector<Record>& myRecord) {
	int choice;
	std::string nameS, nameE;
	std::string date = formatdate("Enter the date [DDMMYYYY] (Enter 99 to cancel): "); //the function is used to change the date to DDMMYYYY format

	if (date == "99") {
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
		choice = integerinputfilter("Choose an option (1/2) (Enter 99 to cancel): ");
		if (choice == -1) {
			std::cout << "\nInvalid input! Do not include alphabet or symbols!\n";
			continue;
		}
		if (choice == -2) {
			std::cout << "\nInput cannot be empty!\n";
			continue;
		}
		if (choice == 99) {
			std::cout << "\nAdd record cancelled.\n";
			clearscreen();
			return;
		}
		if (choice == 1) {
			nameS = stringinputfilter("Enter the name of the savings (Enter 99 to cancel): ");
			if (nameS == "99") {
				std::cout << "\nAdded Cancelled.\n";
				clearscreen();
				return;
			}
			double validSavings = 0.0;
			while (true) {
				double inputval = doubleinputfilter("Enter the amount of the savings (Enter 99 to cancel): ");

				if (inputval == -1) {
					std::cout << "\nInvalid input! Do not include alphabet or symbols!\n";
					continue;
				}
				else if (inputval == -2) {
					std::cout << "\nInput cannot be empty!\n";
					continue;
				}
				else if (inputval == -3) {
					std::cout << "\nInput cannot include negative.\n";
					continue;
				}
				else if (inputval == 99) {
					std::cout << "\nAdded Cancelled.\n";
					clearscreen();
					return;
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
			nameE = stringinputfilter("Enter the name of the expense (Enter 99 to cancel): ");
			if (nameE == "99") {
				std::cout << "\nAdded Cancelled.\n";
				clearscreen();
				return;
			}
			while (true) {
				double inputval = doubleinputfilter("Enter the amount of the expense (Enter 99 to cancel): ");

				if (inputval == -1) {
					std::cout << "\nInvalid input! Do not include alphabet or symbols!\n";
					continue;
				}
				else if (inputval == -2) {
					std::cout << "\nInput cannot be empty!\n";
					continue;
				}
				else if (inputval == 99) {
					std::cout << "\nAdded Cancelled\n";
					clearscreen();
					return;
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
		clearscreen();
		return;
	}
	size_t index = currentUser.myRecord.size();
	//sort record date with selection sort
	for (size_t i = 0; i < index - 1; ++i) {
		size_t minIndex = i;
		for (size_t j = i + 1; j < index; ++j) {
			if (currentUser.myRecord[j].date < currentUser.myRecord[minIndex].date) {
				minIndex = j;
			}
		}
		if (minIndex != i) {
			std::swap(currentUser.myRecord[i], currentUser.myRecord[minIndex]);
		}
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
	std::cout << "- ---------- - -------------------- - -------------------- - ---------- - ---------- -\n\n";

	std::string finddate = formatdate("Enter the date to update [DDMMYYYY] (Enter 99 to cancel): ");

	if (finddate == "99") {
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
	int choice = integerinputfilter("Enter your choice (1/2) (Enter 99 to cancel): ");
	if (choice == 99) {
		std::cout << "\nUpdate Cancelled.\n";
		clearscreen();
		return;
	}
	if (choice == 1) {
		std::cout 
			<< "\n--------------------------------------"
			<< "\nCurrent Name: " << currentUser.myRecord[foundindex].nameS
			<< "\nCurrent Savings: " << currentUser.myRecord[foundindex].savings
			<< "\n--------------------------------------\n";

		nameS = stringinputfilter("Enter new name (Enter 99 to cancel): ");
		if (nameS == "99") {
			std::cout << "\nUpdate Cancelled.\n";
			clearscreen();
			return;
		}

		double validSavings = 0.0;
		while (true) {
			double inputval = doubleinputfilter("Enter new savings (Enter 99 to cancel): ");

			if (inputval == -1) {
				std::cout << "\nInvalid input! Do not include alphabet or symbols!\n";
				continue;
			}
			else if (inputval == -2) {
				std::cout << "\nInput cannot be empty!\n";
				continue;
			}
			else if (inputval == 99) {
				std::cout << "\nUpdate Cancelled\n";
				clearscreen();
				return;
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
	else if (choice == 2) {
		std::cout 
				<< "\n--------------------------------------"
				<< "\nCurrent Name: " << currentUser.myRecord[foundindex].nameE
				<< "\nCurrent Balance: " << currentUser.myRecord[foundindex].expenses
				<< "\n--------------------------------------\n";

		nameE = stringinputfilter("Enter new name (Enter 99 to cancel): ");
		if (nameE == "99") {
			std::cout << "\nUpdate cancelled.\n";
			clearscreen();
			return;
		}

		double validExpense = 0.0;
		while (true) {
			double inputval = doubleinputfilter("Enter new expense (Enter 99 to cancel): ");

			if (inputval == -1) {
				std::cout << "\nInvalid input! Do not include alphabet or symbols!\n";
				continue;
			}
			else if (inputval == -2) {
				std::cout << "\nInput cannot be empty!\n";
				continue;
			}
			else if (inputval == -3) {
				std::cout << "\nInput cannot include negative.\n";
				continue;
			}
			else if (inputval == 99) {
				std::cout << "\nUpdate Cancelled\n";
				clearscreen();
				return;
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

void displayrecord(User& currentUser, std::vector<Record>& myRecord) {
	if (currentUser.myRecord.empty()) {
		std::cout << "\nNo record found.\n";
		clearscreen();
		return;
	}
	double totalSavings = 0.0;
	double totalExpenses = 0.0;
	double totalbalance;
	while (true) {
		std::cout
			<< "\n-------------------------------"
			<< "\n| 1. Display Monthly Savings  |"
			<< "\n| 2. Display All Savings      |"
			<< "\n-------------------------------\n";
		int option;
		option = integerinputfilter("Enter option 1 or 2 (Enter 99 to cancel): ");
		if (option == -1) {
			std::cout << "\nInvalid input! Do not include alphabet or symbols!\n";
			continue;
		}
		else if (option == -2) {
			std::cout << "\nInput cannot be empty!\n";
			continue;
		}
		else if (option == 99) {
			std::cout << "\nDisplay Record Cancelled.\n";
			clearscreen();
			return;
		}
		else if (option == 1) {
			int month;
			const std::string monthName[] = {
				"", "JANUARY", "FEBRUARY", "MARCH", "APRIL", "MAY", "JUNE",
				"JULY", "AUGUST", "SEPTEMBER", "OCTOBER", "NOVEMBER", "DECEMBER"
			};

			std::cout
				<< std::setw(44) << "------------------------------------------\n"
				<< std::setw(44) << "|          All Monthly Records           |\n"
				<< std::setw(44) << "------------------------------------------\n"
				<< std::setw(44) << "|    1. January     |     7. July        |\n"
				<< std::setw(44) << "|    2. February    |     8. August      |\n"
				<< std::setw(44) << "|    3. March       |     9. September   |\n"
				<< std::setw(44) << "|    4. April       |    10. October     |\n"
				<< std::setw(44) << "|    5. May         |    11. November    |\n"
				<< std::setw(44) << "|    6. June        |    12. December    |\n"
				<< std::setw(44) << "------------------------------------------\n";

			month = integerinputfilter("Enter the number 1 to 12 to display monthly record (Enter 99 to cancel): ");
			if (month == -1) {
				std::cout << "\nInvalid input! Do not include alphabet or symbols!\n";
				continue;
			}
			else if (month == -2) {
				std::cout << "\nInput cannot be empty!\n";
				continue;
			}
			else if (month == 99) {
				std::cout << "\nDisplay Month Cancelled.\n";
				clearscreen();
				return;
			}
			else {
				std::cout << "\nInvalid month. Please choose from 1 to 12 only.\n";
				continue;
			}
			bool found = false;
			size_t index = currentUser.myRecord.size();
			//sort record date with selection sort
			for (size_t i = 0; i < index - 1; ++i) {
				size_t minIndex = i;
				for (size_t j = i + 1; j < index; ++j) {
					if (currentUser.myRecord[j].date < currentUser.myRecord[minIndex].date) {
						minIndex = j;
					}
				if (minIndex != i) {
					std::swap(currentUser.myRecord[i], currentUser.myRecord[minIndex]);
				}
			}
		}
				
		for (const auto& r : currentUser.myRecord) {
			std::string monthstr = r.date.substr(3, 2);
			int recordmonth = std::stoi(monthstr);
			if (recordmonth == month) {
				if (!found) {
					std::string titleMonth = monthName[month] + " MONTHLY RECORD";
					std::cout //first display the header
						<< "\n--------------------------------------------------------------------------------------"
						<< "\n| "  << std::right <<  std::setw(53) << titleMonth << std::setw(31) << " |"
						<< "\n- ---------- - -------------------- - -------------------- - ---------- - ---------- -"
						<< "\n|    Date    |     Savings'Name     |     Expenses'Name    |   Savings  |  Expenses  |"
						<< "\n- ---------- - -------------------- - -------------------- - ---------- - ---------- -\n";
					found = true;
				}
				//then display all the record
			std::cout << std::left << std::fixed << std::setprecision(2)
				<< "| " << std::setw(11) << r.date
				<< "| " << std::setw(21) << r.nameS
				<< "| " << std::setw(21) << r.nameE
				<< "| " << std::setw(11) << r.savings
				<< "| " << std::setw(11) << r.expenses
				<< "|" << std::endl;
			totalSavings += r.savings;
			totalExpenses += r.expenses;
			}
		}
		//after looping all the records, then only print the rest of the line to avoid the menu being looped twice
		if (found) {
			std::cout << "- ---------- - -------------------- - -------------------- - ---------- - ---------- -\n";
			totalbalance = totalSavings - totalExpenses;
			std::cout
				<< "\n- ------------------------------ -"
				<< "\n| Total Savings   : RM " << std::setw(8) << totalSavings << "  |"
				<< "\n| Total Expenses  : RM " << std::setw(8) << totalExpenses << "  |"
				<< "\n| Current Balance : RM " << std::setw(8) << totalbalance << "  |"
				<< "\n- ------------------------------ -\n";
			clearscreen();
		}
		else {
			std::cout << "\nNo records found on this month.\n";
			clearscreen();
			return;
		}	
	}				
	else if (option == 2) {
		std::string dayJ, monthJ, yearJ, dayMin, monthMin, yearMin;
		size_t index = currentUser.myRecord.size();
		//sort record date with selection sort
		for (size_t i = 0; i < index - 1; ++i) {
			size_t minIndex = i;
			for (size_t j = i + 1; j < index; ++j) {
				dayJ = currentUser.myRecord[j].date.substr(0, 2);		//first insert day, month and year into string j and minIndex
				monthJ = currentUser.myRecord[j].date.substr(3, 2);
				yearJ = currentUser.myRecord[j].date.substr(6, 4);
				std::string sortDateJ = yearJ + monthJ + dayJ; //changing it from DDMMYYYY to YYYYMMDD to detect the ascending order of date

				dayMin = currentUser.myRecord[minIndex].date.substr(0, 2);
				monthMin = currentUser.myRecord[minIndex].date.substr(3, 2);
				yearMin = currentUser.myRecord[minIndex].date.substr(6, 4);
				std::string sortDateMin = yearMin + monthMin + dayMin;
				if (sortDateJ < sortDateMin) {			//compare if dateJ is smaller than dateMin, then swap position
					minIndex = j;
				}
			}
			if (minIndex != i) {
				std::swap(currentUser.myRecord[i], currentUser.myRecord[minIndex]);
			}
		}
		//Remark: Why not using DDMMYYYY format?
		/*Ans: Lets say we have two date 01032026 and 25092025. 01032025 is suppose to be smaller than 25092026. So if we use DDMMYYYY, it will first detect
		 the DD which is 01 and 25, 25 is larger than 01, so it will swap position, then it will stop detecting the rest of the number, however, 
		 by using YYYYMMDD format, the detection will be like year: 2025 compare 2026, month: 03 compare 09, day: 01 compare 25, so that it will successfully sort it properly.*/

		std::cout
			<< "\n--------------------------------------------------------------------------------------"
			<< "\n|                                ALL MONTHLY RECORD                                  |"
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
			<< "\n| Current Balance : RM " << std::setw(8) << totalbalance << "  |"
			<< "\n- ------------------------------ -\n";
		clearscreen();
	}
	else {
		std::cout << "\nInvalid number. You can only type 1, 2 or 99.\n";
		return;
	}
	break;
	}
}

void deleterecord(User& currentUser, std::vector<Record>& myRecord) {
	std::string deletedate;
	if (currentUser.myRecord.empty()) {
		std::cout << "\nNo record found.\n";
		clearscreen();
		return;
	}
	std::string dayJ, monthJ, yearJ, dayMin, monthMin, yearMin;
	size_t index = currentUser.myRecord.size();
	//sort record date with selection sort
	for (size_t i = 0; i < index - 1; ++i) {
		size_t minIndex = i;
		for (size_t j = i + 1; j < index; ++j) {
			dayJ = currentUser.myRecord[j].date.substr(0, 2);		//first insert day, month and year into string j and minIndex
			monthJ = currentUser.myRecord[j].date.substr(3, 2);
			yearJ = currentUser.myRecord[j].date.substr(6, 4);
			std::string sortDateJ = yearJ + monthJ + dayJ; //changing it from DDMMYYYY to YYYYMMDD to detect the ascending order of date

			dayMin = currentUser.myRecord[minIndex].date.substr(0, 2);
			monthMin = currentUser.myRecord[minIndex].date.substr(3, 2);
			yearMin = currentUser.myRecord[minIndex].date.substr(6, 4);
			std::string sortDateMin = yearMin + monthMin + dayMin;
			if (sortDateJ < sortDateMin) {		//compare if dateJ is smaller than dateMin, then swap position
				minIndex = j;
			}
		}
		if (minIndex != i) {
			std::swap(currentUser.myRecord[i], currentUser.myRecord[minIndex]);
		}
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
	std::cout << "- ---------- - -------------------- - -------------------- - ---------- - ---------- -\n\n";

	deletedate = formatdate("Enter date to delete [DDMMYYYY] (Enter 99 to cancel):");
	if (deletedate == "-1") {
		std::cout << "\nInvalid input! Do not include alphabet or symbols!\n";
		return;
	}
	else if (deletedate == "-2") {
		std::cout << "\nInput cannot be empty!\n";
		return;
	}
	else if (deletedate == "99") {
		std::cout << "\nDelete Cancelled.\n";
		clearscreen();
		return;
	}
	bool founddate = false;
	for (auto i = currentUser.myRecord.begin(); i != currentUser.myRecord.end(); ++i) {
		if (i->date == deletedate) {
			currentUser.myRecord.erase(i);
			founddate = true;
			break;
		}
	}
	saveUserRecord(currentUser);
	std::cout << "\nSuccessfully deleted!\n";
	clearscreen();

	if (!founddate) {
		std::cout << "\nDate " << deletedate << " is not found in record.\n";
		clearscreen();
		return;
	}
}