#pragma once
#include <string>

using namespace std;

class Node
{
public:
    string val;
    int productionNr = 0;
    Node* leftChild = nullptr;
    Node* rightSibling = nullptr;

    Node(string _val = "") : val{_val} {}
    ~Node() {
        if (leftChild != nullptr) {
            delete leftChild;
        }
        if (rightSibling != nullptr) {
            delete rightSibling;
        }
    }
};

