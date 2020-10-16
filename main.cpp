#include <iostream>
#include <vector>

using namespace std;


class ST {
public:
    ST() {
        st.resize(initialSize);
    }

    void add(string val) {
        if(!exists(val))
            st[hashing(val)].push_back(val);
    }

    bool exists(string val) {
        int idx = hashing(val);
        for(auto& v : st[idx])
            if(v == val) {
                return true;
            }
        return false;
    }

    void remove(string val) {
        int idx = hashing(val);
        for (auto it = st[idx].begin(); it != st[idx].end(); ++it) 
            if(*it == val)
                st[idx].erase(it);
    }

    void _printState() {
        cout << "ST\n";
        for (int i = 0; i < st.size(); ++i) {
            auto v = st[i];
            cout << i << ": ";
            for (auto it = v.begin(); it != v.end(); ++it) 
                cout << *it << ' ';
            cout << '\n';
        }
    }

private:
    int hashing(string val) {
        int sum = 0;
        for(auto& c : val) {
            sum += c - '0';
        }
        return sum  % st.size();
    }

    vector<vector<string>> st;
    const int initialSize = 7;
};

int main() {
    ST st;
    st.add("a11");
    st.add("a12");
    st.add("a21");

    cout << "a11 exists: " << st.exists("a11") << '\n';
    cout << "a12 exists: " << st.exists("a12") << '\n';
    cout << "a13 exists: " << st.exists("a13") << '\n';
    cout << '\n';

    st._printState();
    return 0;
}