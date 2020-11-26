#pragma once
#include <stack>
#include <string>
#include <vector>
#include "grammar.h"

using namespace std;

class Element {
public:
	string val;
	int productionNr; // -1 for terminals

	Element(string _val = "", int _productionNr = 0) : val{ _val }, productionNr{ _productionNr } {}
};


class Parser
{
private:
	Grammar g;
	vector<string> sequence;
	Element start;
	char state = 'q';
	unsigned int index = 0;
	stack<Element> alpha;
	stack<Element> beta;

	void Expand();
	void Advance();
	void MomentaryInsucces();
	void Back();
	void AnotherTry();
	void Succes();

	bool IsNonterminal(string el);
public:
	Parser(Grammar _g) : g{ _g } {}
	bool Solve(vector<string> sequence);
	vector<Element> GetProductionString();
};

