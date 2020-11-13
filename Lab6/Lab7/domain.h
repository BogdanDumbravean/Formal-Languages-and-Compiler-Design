#include <string>
#include <vector>

using namespace std;

class Transition {
public:
    string startState, resultedState;
    char alphabetElement;
    Transition(string _startState, char _languageElement, string _resultedState)
        : startState(_startState), alphabetElement(_languageElement), resultedState(_resultedState) {}
};

class FA {
public:
    vector<string> states, finals;
    vector<char> alphabet;
    string start;
    vector<Transition> transitions;
};


class Solver {
private:
    FA fa;

    // Searches recursively through each character of the sequences to find if it is accepted by the FA 
    // Input: sequence - string that needs to be verified
    //	    currentState – state at which the program is in the moment of execution
    //      idx - index at which the program is in the moment of execution
    //      size - length of the sequence
    // Output: - true, if FA accepts sequence
    //          - false, otherwise
    // Preconditions: Call with the starting state as currentState, idx 0 and size equal to size of the sequence 
    bool findNextState(const string sequence, const string currentState, const int idx, const int size);
public:
    Solver(FA _fa) : fa(_fa) {}

    // Verifies if the FA given is deterministic
    // Output: - true, if FA is deterministic
    //          - false, otherwise
    bool checkDeterministic();


    // Verifies if the sequence is accepted by the FA (by using findNextState method)
    // Input: sequence - string that needs to be verified
    // Output: - true, if FA accepts sequence
    //          - false, otherwise
    bool testSequence(string sequence);
};
