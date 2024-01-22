#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

extern int n, m;
extern std::vector<std::vector<int>> e;

void file_to_adjmat(std::string path);