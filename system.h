#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include "models.h"

void managemenu(User& currentUser, std::vector<Record>& myRecord);
void addrecord(User& currentUser, const std::vector<Record>& myRecord);
void updaterecord(User& currentUser, std::vector<Record>& myRecord);
void displayrecord(User& currentUser, const std::vector<Record>& myRecord);

#endif