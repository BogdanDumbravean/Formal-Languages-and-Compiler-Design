#include "scanner.h"
#include <iostream>

#include <sstream>

using namespace std;

int main() {
    Scanner scanner;
    cout << scanner.scan("token.in", "p2.txt", "PIF.out", "ST.out");
}