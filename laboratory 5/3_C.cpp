#include "blazingio.hpp"
#include <vector>
using namespace std;



long long hach_fun(long long &sizeTable, long long &appendElement) {
    return (appendElement + 401) % sizeTable;
}


bool findEl(vector<vector<long long>> &closeHashTable, long long &el, long long &sizeTable) {
    long long ind = hach_fun(sizeTable, el);
    for(int i = 0; i < closeHashTable[ind].size(); i++) {
        if(closeHashTable[ind][i] == el) {
            return true;
        }
    }
    return false;
}


int main() {
    long long n, i;
    cin >> n;

    vector<vector<long long>> closeHashTable(n, vector<long long>());
    long long el;
    for(i = 0; i < n; i++) {
        cin >> el;
        closeHashTable[hach_fun(n, el)].push_back(el);
    }


    bool flag = true;
    for(i = 0; i < n; i++) {
        cin >> el;
        if(findEl(closeHashTable, el, n) == false) {
            flag = false;
            break;
        }
    }

    if(flag == true)
        cout << "YES";
    else
        cout << "NO";
    return 0;
}
