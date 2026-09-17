#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "system.h"
#include "models.h"

void saveUserRecord(User& currentUser) {
	std::vector<std::string>updatedlines;
	std::ifstream inFile("user_record.txt");
	std::string line;

	std::vector<bool> recordUpdated(currentUser.myRecord.size(), false);

	while (std::getline(inFile, line)) {
		if (line.empty()) {
			continue;
		}
		//check whether this line is belongs to currentuser
		if (line.find(currentUser.username + ",") == 0) {
			for (size_t i = 0; i < currentUser.myRecord.size(); ++i) {
				const auto& r = currentUser.myRecord[i];
				std::string user_date = currentUser.username + "," + r.date + ",";

				if (line.find(user_date) == 0) {
					line = user_date + r.nameS + "," + r.nameE + "," + std::to_string(r.savings) + "," + std::to_string(r.expenses);
					recordUpdated[i] = true;
					break;
				}
			}
		}
		updatedlines.push_back(line);
	}
	inFile.close(); 

	for (size_t i = 0; i < currentUser.myRecord.size(); ++i) {
		if (!recordUpdated[i]) {
			const auto& r = currentUser.myRecord[i];
			std::string newline = currentUser.username + "," + r.date + "," + r.nameS + "," + r.nameE + "," + std::to_string(r.savings) + "," + std::to_string(r.expenses);
			updatedlines.push_back(newline);
		}
	}

	std::ofstream outfile("user_record.txt");
	for (const auto& l : updatedlines) {
		outfile << l << '\n';
	}
	outfile.close();
}

void readUserRecord(User& currentUser) {
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