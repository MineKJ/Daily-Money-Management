#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "system.h"
#include "models.h"

void saveUserRecord(const User& currentUser ) {
	std::vector<std::string>updatedlines;
	std::ifstream inFile("user_record.txt");
	std::string line;

	while (std::getline(inFile, line)) {
		if (line.empty()) {
			continue;
		}
		//check whether this line is belongs to currentuser
		if (line.find(currentUser.username + ",") == 0) {
			for (const auto& r : currentUser.myRecord) {
				std::string user_date = currentUser.username + "," + r.date + ",";

				if (line.find(user_date) == 0) {
					line = user_date + r.nameS + "," + r.nameE + "," + std::to_string(r.savings) + "," + std::to_string(r.expenses);
					break;
				}
			}
		}
		updatedlines.push_back(line);
	}
	inFile.close();

	std::ofstream outfile("user_record.txt");
	for (const auto& l : updatedlines) {
		outfile << l << '\n';
	}
	outfile.close();
}

void readUserRecord(User& currentUser) {
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
			std::getline(ss, expensesStr, ',')) {

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