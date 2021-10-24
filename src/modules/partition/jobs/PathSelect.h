/*
 *   SPDX-FileCopyrightText: 2021 Kiyung <yongjae.choi20@gmail.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef BACKUP_H
#define BACKUP_H

#include <filesystem>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include <unistd.h>

namespace fs = std::filesystem;


std::string selectPath();

std::string getLastPathToken(std::string str);

#endif

