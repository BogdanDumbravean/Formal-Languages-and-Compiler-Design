#include <string>
#include "ST.h"
#include <map>

using namespace std;

class Scanner{
private:
    bool useRegex;
    ST st;
    map<string, int> tokens;
    vector<pair<string, int>> pif;

    void write(string pifFile, string stFile);
    void readTokens(string tokenFile);
    vector<string> split(string s, string delimiter);
    bool addWordToPif(string word);
    bool checkConstant(string word);
    bool checkIdentifier(string word);
public:
    Scanner(string configFile);
    string scan(string tokenFile, string programFile, string pifFile, string stFile);
};