#include "ui.h"

int main() {
    Reader r;
    r.read("FA.in");
    Solver s(r.fa);
    UI ui(r.fa, s);
    ui.start();
    return 0;
}