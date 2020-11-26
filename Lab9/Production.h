#pragma once
#include <string>
#include <vector>

using namespace std;

class Production {
public:
    string start;
    vector<vector<string>> results;
    Production() {}
    Production(string _start, vector<vector<string>> _results)
        : start(_start), results(_results) {}

    string ToString();
};