#ifndef MODELS_H
#define MODELS_H

#include <string>
#include <vector>

struct Record {
	std::string date;
	std::string nameS;
	std::string nameE;
	double savings = 0.0;
	double expenses = 0.0;
};

struct User {
	std::string username;
	std::string password;
	std::vector<Record> myRecord;
};

#endif