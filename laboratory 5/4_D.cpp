#include "blazingio.hpp"
#include <vector>
#include <string>
using namespace std;

struct Node {
    int isu, points, number_group;
};

int hash_fun(int &sizeTable, int &appendElement, int &k) {
    return (abs(appendElement + k * k)) % sizeTable;
}


void append_hash_table(int n, vector<vector<Node>> &closeHashTable, int &group, Node &buf) {
    int ind;
    for(int k = 0; k < n; k++) {
        ind = hash_fun(n, group, k);

        if(closeHashTable[ind].size() == 0) {
            closeHashTable[ind].push_back(buf);
            break;
        }
        else if(closeHashTable[ind][0].number_group == buf.number_group) {
            closeHashTable[ind].push_back(buf);
            break;
        }
        else {
            continue;
        }
    }
}


int sredn_ball_group(int n, vector<vector<Node>> &closeHashTable, int &group) {
    int ind;
    int summa = 0, count;
    for(int k = 0; k < n; k++) {
        ind = hash_fun(n, group, k);

        if(closeHashTable[ind][0].number_group == group) {
            count = closeHashTable[ind].size();
            for(int i = 0; i < closeHashTable[ind].size(); i++) {
                summa += closeHashTable[ind][i].points;
            }
            break;
        }
        else {
            continue;
        }
    }
    return (int)(summa / count);
}


int max_ball_group(int n, vector<vector<Node>> &closeHashTable, int &group) {
    int ind;
    int maxBall = 0;
    for(int k = 0; k < n; k++) {
        ind = hash_fun(n, group, k);

        if(closeHashTable[ind][0].number_group == group) {
            for(int i = 0; i < closeHashTable[ind].size(); i++) {
                maxBall = max(maxBall, closeHashTable[ind][i].points);
            }
            break;
        }
        else {
            continue;
        }
    }
    return maxBall;
}


void delete_people(int n, vector<vector<Node>> &closeHashTable, int &group, int &isu) {
    int ind;
    for(int k = 0; k < n; k++) {
        ind = hash_fun(n, group, k);

        if(closeHashTable[ind][0].number_group == group) {
            for(int p = 0; p < closeHashTable[ind].size(); p++) {
                if(closeHashTable[ind][p].isu == isu) {
                    closeHashTable[ind].erase(closeHashTable[ind].begin() + p);
                    break;
                }
            }
            break;
        }
    }
}


int main() {
    long long groupCount, requestCount;
    cin >> groupCount >> requestCount;


    vector<vector<Node>> closeHashTable(groupCount, vector<Node>());

    char input;
    Node buf;
    for(int i = 0; i < requestCount; i++) {
        cin >> input;

        if(input == '+') {
            int group, isu, points;
            cin >> group >> isu >> points;
            buf.isu = isu; buf.points = points; buf.number_group = group;
            append_hash_table(groupCount, closeHashTable, group, buf);
        }

        else if(input == 'a') {
            int group; cin >> group;
            cout << sredn_ball_group(groupCount, closeHashTable, group) << "\n";
        }

        else if(input == 'm') {
            int group; cin >> group;
            cout << max_ball_group(groupCount, closeHashTable, group) << "\n";
        }

        else if(input == '-') {
            int group, isu; cin >> group >> isu;
            delete_people(groupCount, closeHashTable, group, isu);
        }
    }
}

/*
5 5
+ 1 10 3
+ 1 2 4
+ 1 2 5
a 1
m 1


16 2
+ 8 10 10
+ 24 14 9


14 5
+ 3 10 10
+ 3 13 15
m 3
- 3 10
m 3

14 5
+ 3 10 10
+ 3 13 15
a 3
- 3 10
a 3
*/
