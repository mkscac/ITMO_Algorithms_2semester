#include <iostream>
#include <vector>
using namespace std;


void DFS(vector<vector<long long>> &graph, vector<bool> &visited, long long cur_vertex) {
    visited[cur_vertex] = 1;

    for(int U: graph[cur_vertex]) {
        if(visited[U] == 0) {
            DFS(graph, visited, U);
        }
    }
}


int fun_countComponents(vector<vector<long long>> &graph, vector<bool> &visited, long long n) {
    int countComponents = 0;

    for(long long V = 0; V < n; V++) {
        if(visited[V] == 0) {
            DFS(graph, visited, V);
            countComponents ++;
        }
    }
    return countComponents;
}



int main() {
    long long vertexCount, edgeCount, i;
    cin >> vertexCount >> edgeCount;


    vector<bool> visited(vertexCount, 0);
    vector<vector<long long>> graph(vertexCount, vector<long long>());


    for(i = 0; i < edgeCount; i++) {
        long long el1, el2;
        cin >> el1 >> el2;
        graph[el1-1].push_back(el2-1);
        graph[el2-1].push_back(el1-1);
    }


    int res = fun_countComponents(graph, visited, vertexCount);
    if((res == 1) && (vertexCount == edgeCount)) {
        cout << "ARCHIMEDES";
    } else {
        cout << "EUCLID";
    }

    return 0;
}
