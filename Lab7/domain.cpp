#include <map>
#include <set>
#include "domain.h"


bool Solver::checkDeterministic() {
    map<string, set<char>> elems;
    for(const auto& t : fa.transitions) {
        if(elems[t.startState].find(t.alphabetElement) != elems[t.startState].end())
            return false;
        elems[t.startState].insert(t.alphabetElement);
    }
    return true;
}

bool Solver::findNextState(const string sequence, const string currentState, const int idx, const int size) {
    
    if(idx == size) {
        for(const auto& f : fa.finals)
            if(f == currentState)
                return true;
        return false;
    }
    
    for(const auto& t : fa.transitions) {
        if(t.startState == currentState && t.alphabetElement == sequence[idx]) {
            if(findNextState(sequence, t.resultedState, idx + 1, size))
                return true;
        }
    }
    return false;
}

bool Solver::testSequence(string sequence) {
    return findNextState(sequence, fa.start, 0, sequence.size());
}

