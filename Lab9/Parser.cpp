#include "Parser.h"
#include <iostream>

void Parser::Expand() {
	// if top(beta) is nonterminal
	Element el = beta.top();
	el.productionNr = 1;
	alpha.push(el); 
	beta.pop();

	vector<vector<string>> results = g.GetNonterminalProductions(el.val).results;

	for (int i = results[0].size() - 1; i >= 0; --i) {
		string s = results[0][i];
		beta.push(Element(s)); 
	}
}

void Parser::Advance() {
	// when top(beta) == current symbol from input
	index++; 
	alpha.push(beta.top()); 
	beta.pop();
}

void Parser::MomentaryInsucces() {
	// when top(beta) != current symbol from input
	state = 'b';
}

void Parser::Back() {
	// when top(alpha) is terminal
	index--;
	beta.push(alpha.top()); 
	alpha.pop();
}

void Parser::AnotherTry() {
	// when top(alpha) is nonterminal
	Element el = alpha.top();
	if (index == 0 && el.val.compare(start.val) == 0) {
		cout << "Error! " << state << ' ' << index << ' ' << el.val << ' ' << el.productionNr << '\n';
		state = 'e';
		return;
	}
	vector<vector<string>> results = g.GetNonterminalProductions(el.val).results;
	alpha.pop();
	for (size_t i = 0; i < results[el.productionNr - 1].size(); ++i)
		beta.pop();
	if (results.size() == el.productionNr) {
		el.productionNr = 0;
		beta.push(el); 
	}
	else {
		state = 'q';
		el.productionNr++;
		alpha.push(el); 
		for (int i = results[el.productionNr - 1].size() - 1; i >= 0; --i) {
			string s = results[el.productionNr - 1][i];
			beta.push(Element(s)); 
		}
	}
}

void Parser::Succes() {
	state = 'f';
}

bool Parser::IsNonterminal(string el) {
	for (const auto& x : g.GetNonterminals())
		if (el == x)
			return true;
	return false;
}

bool Parser::Solve(vector<string> seq) {
	this->sequence = seq;
	state = 'q';
	index = 0;
	start = Element(g.GetStartingSymbol());
	alpha = stack<Element>();
	beta = stack<Element>();
	beta.push(start); 

	while (state != 'f' && state != 'e') { 

		if (state == 'q') {
			if (beta.empty() && index == sequence.size())
				Succes();
			else {
				if (beta.empty()) {
					MomentaryInsucces();
					continue;
				}
				Element top = beta.top();
				if (IsNonterminal(top.val))
					Expand();
				else if (index < sequence.size() && top.val == sequence[index])
					Advance();
				else MomentaryInsucces();
			}
		}
		else if (state == 'b') {
			Element top = alpha.top();
			if (IsNonterminal(top.val))
				AnotherTry();
			else
				Back();
		}
	}

	if (state == 'e')
		return false;
	return true;
}

vector<Element> Parser::GetProductionString() {
	vector<Element> aux;
	while (!alpha.empty()) {
		if(IsNonterminal(alpha.top().val)) 
			aux.push_back(alpha.top());
		alpha.pop();
	}
	reverse(aux.begin(), aux.end());
	return aux;
}