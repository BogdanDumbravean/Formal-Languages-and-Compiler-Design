#include "scanner.h"
#include <fstream>
#include <sstream>
#include <regex>

using namespace std;

void Scanner::write(string pifFile, string stFile) {
    ofstream pifout("PIF.out");
    ofstream stout("ST.out");
    
    for (auto const& p : pif) {
        pifout << p.first << ' ' << p.second << '\n';
    }
    stout << st._getState();

    pifout.close();
    stout.close();
}

void Scanner::readTokens(string tokenFile) {
    ifstream tin(tokenFile);
    int id;
    string token;
    // Read constants and identifiers outside of tokens?
    tin >> id >> token;
    tin >> id >> token;
    while (tin >> id >> token) {
        tokens.insert({ token, id });
    }
    tin.close();
}

vector<string> Scanner::split(string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

bool Scanner::addWordToPif(const string word) {
    bool isCorrect = true;
    if (word == "")
        return isCorrect;

    if (tokens.find(word) != tokens.end()) {
        pif.push_back({ word, -1 });
        //cout << "found token: " + word << '\n';
        return isCorrect;
    }

    // Search for complex separators (in case of >=, <>, etc):
    vector<string> aux;
    aux.push_back(word);
    for (auto const& x : tokens) {
        size_t pos = word.find(x.first);
        if (x.first.size() > 1 && pos != string::npos) {
            //std::cout << "x: " << x.first << '\n';
            aux = split(word, x.first);

            for (int i = 0; i < aux.size(); ++i)
                if (aux[i] != "") {
                    if (!addWordToPif(aux[i]))
                        isCorrect = false;
                    pif.push_back({ x.first, -1 });
                }
            return isCorrect;
        }
    }

    // Cauta retul operatorilor (cei simpli)
    for (auto const& x : tokens) {
        size_t pos = word.find(x.first);
        if(x.first.size() == 1 && pos != string::npos) {

            aux = split(word, x.first);
            //addWordToPif(aux[0]);
            //pif.insert({ word, -1 });
            for (int i = 0; i < aux.size(); ++i) 
                if(aux[i] != ""){
                    if (!addWordToPif(aux[i]))
                        isCorrect = false;
                    pif.push_back({ x.first, -1 });
                }
            return isCorrect;
        }
    }

    // Check that what is left is constant/identifier
    if (regex_match(word, regex("_?[a-zA-Z][a-zA-Z0-9]*"))
        || regex_match(word, regex("[+-]?[1-9][0-9]*"))
        || word == "0"
        || regex_match(word, regex("\"[a-zA-Z0-9]*\""))) {
        int idx = st.add(word);
        pif.push_back({ word, idx });
    }
    else {
        //cout << "error\n";
        isCorrect = false;
    }
    return isCorrect;
}


string Scanner::scan(string tokenFile, string programFile, string pifFile, string stFile) {
    readTokens(tokenFile);

    ifstream pin(programFile);

    string line, word;
    int lineNr = 1;
    istringstream iss; 
    while(getline(pin, line)) {
        iss.clear();
        iss.str(line);
        while (iss >> word) {
            if (!addWordToPif(word))
                return "Lexical Error on line: " + to_string(lineNr) + "; Incorrect Lexic: " + word;
        }
        lineNr++;
    }
    vector<string> result; 

    write(pifFile, stFile);
    pin.close();

    return "Lexically correct!";
}
