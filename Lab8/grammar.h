#include <fstream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

class Production {
public:
    string start;
    vector<vector<string>> results;
    Production() {}
    Production(string _start, vector<vector<string>> _results)
        : start(_start), results(_results) {}

    string ToString() {
        string s = start + "->";
        for (int i = 0; i < results.size(); ++i) {
            for (const auto& a : results[i])
                s += a + ' ';

            if(i < results.size() - 1)
                s += "| ";
        }
        return s;
    }
};

class Grammar {
private:
    vector<string> terminals, nonterminals;
    vector<Production> productions;
    string startingSymbol;

    Production SplitProduction(string production);
public:
    void ReadFromFile(string path);
    vector<string> GetTerminals();
    vector<string> GetNonterminals();
    vector<Production> GetProductions();
    vector<Production> GetNonterminalProductions(string nonterminal);
};