
#include "ui.h"

template <class T>
vector<T> Reader::readVector(ifstream& fin) {
    string line;
    T word;
    vector<T> result;
    getline(fin, line);
    istringstream iss(line);
    while(iss >> word) {
        result.push_back(word);
    }
    return result;
}

void Reader::read(string filename) {
    ifstream fin(filename);
    string line;

    // Read states
    fa.states = readVector<string>(fin);
    // Read alphabet
    fa.alphabet = readVector<char>(fin);
    // Read starting state
    fin >> fa.start;
    fin.get();
    // Read final states
    fa.finals = readVector<string>(fin);

    // Read transitions
    string s, f;
    char l;
    istringstream iss;
    while(getline(fin, line)) {
        iss = istringstream(line);
        iss >> s >> l >> f;
        fa.transitions.push_back({s, l, f});
    }
    fin.close();
}

void UI::printCommands() {
    cout << "\n0 - exit\n1 - check if deterministic\n2 - enter sequence\n3 - print states\n4 - print alphabet\n5 - print transitions\n6 - print final states\n\n";
}

template <class T>
void UI::printVector(vector<T> v) {
    for(const auto& s : v)
        cout << s << ' ';
    cout << '\n';
}

void UI::parseCommand(int command) {
    string sequence;
    switch(command) {
        case 1 : if(s.checkDeterministic())
                    cout << "FA is deterministic\n";
                else
                    cout << "FA NOT deterministic\n";
                break;
        case 2 : if(!s.checkDeterministic()) {
                    cout << "FA NOT deterministic\n";
                } else {
                    cin.get(); 
                    getline(cin, sequence);
                    if(s.testSequence(sequence))  
                        cout << "Sequence matches\n";
                    else
                        cout << "Sequence doesn't match\n";
                }
                break;
        case 3 : cout << "States:\n";
                printVector<string>(fa.states);
                break;
        case 4 : cout << "Alphabet:\n";
                printVector<char>(fa.alphabet);
                break;
        case 5 : cout << "Transitions:\n";
                for(const auto& t : fa.transitions) {
                    cout << '(' << t.startState << ',' << t.alphabetElement << ") -> " << t.resultedState << '\n';
                }
                break;
        case 6 : cout << "Final states:\n";
                printVector<string>(fa.finals);
                break;
        default : cout << "\n\nIncorrect command!\n\n";
    }
}

void UI::start() {
    int command;
    while(true) {
        printCommands();
        cin >> command;
        if(command == 0)
            return;
        parseCommand(command);
    }
}