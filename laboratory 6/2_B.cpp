#include <iostream>
#include <string>
#include <vector>
using namespace std;


bool check(string s1, string s2) {
    for(int i = 0; i < s1.size(); i++)
        if(s1[i] != s2[i])
            return false;
    return true;
}


void prefix_function(string &s, vector<int> &pi) {
    for(int i = 1; i < s.size(); i++) {
        int zn = pi[i-1];

        while(zn > 0 && s[i] != s[zn]) {
            zn = pi[zn-1];
        }
        if(s[i] == s[zn])
            pi[i] = zn + 1;
    }
}



int main() {
    string s; cin >> s;

    vector<int> pi(s.size(), 0);
    prefix_function(s, pi);

    for(int i = 0; i < pi.size(); i++) {
        cout << pi[i] << " ";
    }
    return 0;
}
