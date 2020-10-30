#include "ST.h"
#include <string>

ST::ST() {
    st.resize(initialSize);
}

int ST::add(string val) {
    int index = hashing(val);
    if(!exists(val))
        st[index].push_back(val);
    return index;
}

bool ST::exists(string val) {
    int idx = hashing(val);
    for(auto& v : st[idx])
        if(v == val) {
            return true;
        }
    return false;
}

void ST::remove(string val) {
    int idx = hashing(val);
    for (auto it = st[idx].begin(); it != st[idx].end(); ++it) 
        if(*it == val)
            st[idx].erase(it);
}

string ST::_getState() {
    string result = "";
    for (int i = 0; i < st.size(); ++i) {
        auto v = st[i];
        result += to_string(i) + ": ";
        for (auto it = v.begin(); it != v.end(); ++it) 
            result += *it + ' ';
        result += '\n';
    }
    return result;
}


int ST::hashing(string val) {
    int sum = 0;
    for(auto& c : val) {
        sum += c - '0';
    }
    return sum  % st.size();
}

