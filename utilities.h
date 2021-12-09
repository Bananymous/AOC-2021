#pragma once

#include <stack>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <unordered_set>

#include <cmath>
#include <cstdio>
#include <cstring>

std::vector<int> ReadInts(std::ifstream& file)
{
    std::vector<int> result;
    int temp;
    while(file >> temp)
        result.push_back(temp);
    return result;
}

std::vector<std::string> ReadStrings(std::ifstream& file)
{
    std::vector<std::string> result;
    std::string temp;
    while(file >> temp)
        result.push_back(temp);
    return result;
}

std::vector<int> ParseCSV(std::ifstream& stream)
{
    std::string csv;
    stream >> csv;
    std::vector<int> result;
    int cur = 0;
    for (int i = 0; i <= csv.size(); i++) {
        if (i == csv.size() || csv[i] == ',') {
            result.push_back(cur);
            cur = 0;
        } else cur = (cur * 10) + (csv[i] - '0');
    }
    return result;
}