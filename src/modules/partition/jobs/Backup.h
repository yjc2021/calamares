#ifndef BACKUP_H
#define BACKUP_H

#include <filesystem>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>

namespace fs = std::filesystem;

bool execBackup(std::string from, std::string to);

std::string selectPath();

std::string getLastPathToken(std::string str);

#endif

