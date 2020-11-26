#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include "Production.h"

using namespace std;


class Grammar {
private:
    vector<string> terminals, nonterminals;
    vector<Production> productions;
    string startingSymbol;

    Production SplitProduction(string production);
public:
    void ReadFromFile(string path);
    string GetStartingSymbol() { return startingSymbol; }
    vector<string> GetTerminals();
    vector<string> GetNonterminals();
    vector<Production> GetProductions();
    Production GetNonterminalProductions(string nonterminal);
};