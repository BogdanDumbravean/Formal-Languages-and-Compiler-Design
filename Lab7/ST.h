#include <vector>
#include <iostream>

using namespace std;

class ST {
private:
    vector<vector<string>> st;
    const int initialSize = 7;

    int hashing(string val);
public:  
    ST();
    int add(string val);
    bool exists(string val);
    void remove(string val);
    string _getState();
};