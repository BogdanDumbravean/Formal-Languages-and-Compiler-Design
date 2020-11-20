#include "grammar.h"
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
    for (auto& x : g.GetNonterminalProductions("S"))
        cout << x.ToString() << '\n';
    cout << "\n\n";

    return 0;
}