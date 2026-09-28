#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "system.h"
#include "models.h"

void saveUserRecord(User& currentUser) {
	std::vector<std::string>updatedlines, otherUserData;
	std::ifstream inFile("user_record.txt");
	std::string line;


	if (inFile.is_open()) {
		while (std::getline(inFile, line)) {	//if the line is not for currentuser, then store into a new line
			if (line.find(currentUser.username + ",") != 0) {
				otherUserData.push_back(line);
			}
		}
		inFile.close();

		std::ofstream outfile("user_record.txt");
		for (const auto& l : otherUserData) {
			outfile << l << '\n';
		}

		for (const auto& r : currentUser.myRecord) {
			//if the record is belongs to this user, then store into line
			outfile << currentUser.username << "," << r.date << "," << r.nameS << "," << r.nameE << "," << std::to_string(r.savings) << "," + std::to_string(r.expenses);
		}
		outfile.close();
	}
}

void readUserRecord(User& currentUser) {	//read file
	currentUser.myRecord.clear();
	std::ifstream inFile("user_record.txt");
	std::string line;

	while (std::getline(inFile, line)) {
		std::stringstream ss(line);
		std::string username, date, nameS, nameE, savingsStr, expensesStr;

		if (std::getline(ss, username, ',') &&
			std::getline(ss, date, ',')&&
			std::getline(ss, nameS, ',')&&
			std::getline(ss, nameE, ',') &&
			std::getline(ss, savingsStr, ',')&&
			std::getline(ss, expensesStr )) {

			if (username == currentUser.username) {
				Record r;
				r.date = date;
				r.nameS = nameS;
				r.nameE = nameE;
				r.savings = std::stod(savingsStr);
				r.expenses = std::stod(expensesStr);
				currentUser.myRecord.push_back(r);
			}
		}
	}
	inFile.close();
}