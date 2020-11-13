#include "scanner.h"
#include <iostream>

using namespace std;

int main() {
    Scanner scanner("Input/fa.config");
    cout << scanner.scan("Input/token.in", "Input/p1.txt", "PIF.out", "ST.out");
    return 0;
}