#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


void DFS(long long cur_vertex, vector<vector<long long>> &graph, vector<long long> &visited, long long &k) {
    visited[cur_vertex] = k;

    for(int U: graph[cur_vertex]) {
        if(visited[U] == 0) {
            DFS(U, graph, visited, k);
        }
    }
}


int main() {
    long long n, pairCount, i; cin >> n >> pairCount;

    vector<long long> visited(n, 0);
    vector<vector<long long>> graph(n, vector<long long>());

    for(i = 0; i < pairCount; i++) {
        long long el1, el2; cin >> el1 >> el2;
        graph[el1-1].push_back(el2-1);
        graph[el2-1].push_back(el1-1);
    }


    long long k = 1;
    for(i = 0; i < n; i++) {
        if(visited[i] == 0) {
            DFS(i, graph, visited, k);
            k++;
        }
    }

    cout << *max_element(visited.begin(), visited.end());
    return 0;
}
