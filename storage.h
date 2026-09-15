#ifndef STORAGE_H
#define STORAGE_H

#include "models.h"

void saveUserRecord(const User& currentUser);
void readUserRecord(User& currentUser);

#endif
