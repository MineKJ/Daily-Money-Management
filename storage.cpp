#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "system.h"
#include "models.h"

void saveUserRecord(const User& currentUser ) {
	std::vector<std::string> otherUser;
	std::ifstream inFile("user_record.txt");
	std::string line;

	while (std::getline(inFile, line)) {
		if (line.find(currentUser.username + ",") != 0) { //0 here is like the position of the currentUser u just logged in, this line will skip if is currentuser
			otherUser.push_back(line); //else push back the line into vector otheruser
		}
	}
	inFile.close();

	std::ofstream outfile("user_record.txt");

	//automatically save the other user to otherUser if the above command line.find is not equal to zero
	for (const auto& U : otherUser) {
		outfile << U << '\n';
	}

	for (const auto& r : currentUser.myRecord) {
		outfile << currentUser.username << "," << r.date << "," << r.nameS << " " << r.nameE << "," << r.savings << "," << r.expenses << '\n';
	}
	outfile.close();
}

void readUserRecord(User& currentUser) {
	std::ifstream inFile("user_record.txt");
	std::string line;

	currentUser.myRecord.clear();

	while (std::getline(inFile, line)) {
		std::stringstream ss(line);
		std::string username, date, nameS, nameE, savingsStr, expensesStr;

		if (std::getline(ss, username, ',') &&
			std::getline(ss, date, ',')&&
			std::getline(ss, nameS, ' ')&&
			std::getline(ss, nameE, ',') &&
			std::getline(ss, savingsStr, ',')&&
			std::getline(ss, expensesStr)) {

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