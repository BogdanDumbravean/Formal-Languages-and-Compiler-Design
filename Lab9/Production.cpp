#include "Production.h"

string Production::ToString() {
    string s = start + "->";
    for (int i = 0; i < results.size(); ++i) {
        for (const auto& a : results[i])
            s += a + ' ';

        if (i < results.size() - 1)
            s += "| ";
    }
    return s;
}