#pragma once
#include <vector>
#include <queue>
#include <string>
#include <iostream>
#include "Node.h"
#include "Parser.h"

using namespace std;

class ParserOutput
{
private:
	Node* treeHead = nullptr;
	Grammar g;

	void ParseNode(Node* node, const vector<Element> productionString, int& index);
	void PrintNodeToConsole(Node* node);
public:
	ParserOutput(Grammar _g) : g{ _g } {}
	~ParserOutput() {
		if (treeHead == nullptr)
			return;
		delete treeHead;
	}

	void LeftChildRightSibling(vector<Element> productionString);
	void PrintToConsole();

};

