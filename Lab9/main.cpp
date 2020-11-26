#include "Parser.h"
#include "ParserOutput.h"
#include <iostream>

int main() {
    Grammar g;
    g.ReadFromFile("g1.txt");

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

    cout << "Productions for S:\n";
    cout << g.GetNonterminalProductions("S").ToString() << '\n';
    cout << "\n\n";

    Parser p(g);
    if (p.Solve(vector<string>{ "a", "a", "b", "a" })) {
        cout << "Sequence Accepted";
        cout << "\n\n";

        ParserOutput po(g);
        po.LeftChildRightSibling(p.GetProductionString());
        po.PrintToConsole();
    }
    return 0;
}