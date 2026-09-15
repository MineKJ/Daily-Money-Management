#ifndef TOOLS_H
#define TOOLS_H

#include <iostream>
#include <string>
#include <limits>

int integerinputfilter(const std::string& prompt);
double doubleinputfilter(const std::string& prompt);
std::string stringinputfilter(const std::string& prompt);
void clearscreen();
std::string formatdate(const std::string& prompt);

#endif
