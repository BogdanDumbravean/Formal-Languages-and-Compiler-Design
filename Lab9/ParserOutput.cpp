#include "ParserOutput.h"

void ParserOutput::ParseNode(Node* node, const vector<Element> productionString, int& index) {
	Production p;
	for (const auto& el : productionString) {
		p = g.GetNonterminalProductions(el.val);

		node->leftChild = new Node();
		node = node->leftChild;
		node->val = p.results[el.productionNr - 1][0];

		if (index < productionString.size() && node->val == productionString[index].val) {
			ParseNode(node, productionString, ++index);
		}

		for (int i = 1; i < p.results[el.productionNr - 1].size(); ++i) {
			node->rightSibling = new Node();
			node = node->rightSibling;
			node->val = p.results[el.productionNr - 1][i];

			if (index < productionString.size() && node->val == productionString[index].val) {
				ParseNode(node, productionString, ++index);
			}
		}
	}
}

void ParserOutput::LeftChildRightSibling(vector<Element> productionString) {
	if (productionString.empty())
		return;

	treeHead = new Node();
	treeHead->val = productionString[0].val;
	treeHead->productionNr = productionString[0].productionNr;

	int index = 1;
	ParseNode(treeHead, productionString, index);
	
	treeHead;
}

void ParserOutput::PrintNodeToConsole(Node* node) {
	queue<Node*> next;
	cout << node->val;

	if (node->leftChild != nullptr)
		next.push(node->leftChild);

	Node* aux = node;
	while (aux->rightSibling != nullptr) {
		aux = aux->rightSibling;
		cout << ' ' << aux->val;

		if (aux->leftChild != nullptr)
			next.push(aux);
	}
	cout << '\n';
	if (node->leftChild != nullptr)
		cout << "Left child: " << node->leftChild->val << '\n';
	cout << '\n';

	while (!next.empty()) {
		PrintNodeToConsole(next.front());
		next.pop();
	}
}

void ParserOutput::PrintToConsole() {
	PrintNodeToConsole(treeHead);
}