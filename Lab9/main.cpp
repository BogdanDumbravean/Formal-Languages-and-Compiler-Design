#include "Parser.h"
#include "ParserOutput.h"
#include <iostream>
#include <fstream>

vector<string> ReadPIF(string path) {
    ifstream fin(path);
    vector<string> tokens;
    string line, a, b;
    cout << "Tokens: ";
    while (getline(fin, line)) {
        istringstream iss(line);
        while (iss >> a >> b) {
            tokens.push_back(a);
            cout << a << ' ';
        }
    }
    cout << '\n';
    fin.close();
    return tokens;
}

int main() {
    Grammar g;
    g.ReadFromFile("g2.txt");

    cout << "Terminals:\n" ;
    for(const auto& x : g.GetTerminals())
        cout << x << ' ';
    cout << "\n\n";

    cout << "Nonterminals:\n";
    for (const auto& x : g.GetNonterminals())
        cout << x << ' ';
    cout << "\n\n";

    cout << "Productions:\n";
    for (auto& x : g.GetProductions())
        cout << x.ToString() << '\n';
    cout << "\n\n";

    /*cout << "Productions for S:\n";
    cout << g.GetNonterminalProductions("S").ToString() << '\n';
    cout << "\n\n";*/

    Parser p(g);
    //p.Solve(vector<string>{ "a", "a", "b", "a" })
    if (p.Solve(ReadPIF("PIFp1.in"))) {
        cout << "Sequence Accepted";
        cout << "\n\n";

        ParserOutput po(g);
        po.LeftChildRightSibling(p.GetProductionString());
        po.PrintToConsole();
        po.WriteToFile("tree.out");
    }
    return 0;
}