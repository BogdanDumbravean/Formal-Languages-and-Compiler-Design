#include "grammar.h"

Production Grammar::SplitProduction(string production) {
    size_t pos = production.find("->");

    Production p;
    p.start = production.substr(0, pos);
    p.start.erase(remove(p.start.begin(), p.start.end(), ' '), p.start.end());

    string rhs = production.substr(pos + 2, production.size());
    pos = rhs.find("|");

    while (pos != string::npos) {
        vector<string> elems;
        istringstream iss(rhs.substr(0, pos));
        string a;

        while (iss >> a)
            elems.push_back(a);

        p.results.push_back(elems);
        
        rhs = rhs.substr(pos + 1, rhs.size());
        pos = rhs.find("|");
    }

    vector<string> elems;
    istringstream iss(rhs);
    string a;
    while (iss >> a)
        elems.push_back(a);

    p.results.push_back(elems);
    return p;
}

void Grammar::ReadFromFile(string path) {
    ifstream fin(path);

    string line;
    getline(fin, line);
    istringstream iss(line);
    string a;
    while(iss >> a)
        nonterminals.push_back(a);
    
    getline(fin, line);
    istringstream iss2(line);
    while(iss2 >> a)
        terminals.push_back(a);

    fin >> a;
    fin.get();
    startingSymbol = a;

    while(getline(fin, line)) {
        if(line != "")
            productions.push_back(SplitProduction(line));
    }

    fin.close();
}

vector<string> Grammar::GetTerminals(){
    return terminals;
}
vector<string> Grammar::GetNonterminals(){
    return nonterminals;
}
vector<Production> Grammar::GetProductions(){
    return productions;
}
#include <iostream>
vector<Production> Grammar::GetNonterminalProductions(string nonterminal) {
    vector<Production> res;
    for(const auto& p : productions) 
        if (p.start.compare(nonterminal) == 0) 
            res.push_back(p);
    
    return res;
}