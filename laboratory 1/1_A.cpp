#include <iostream>
#include <vector>
#include <stack>
using namespace std;


void DFS(vector<vector<long long>> &graph, vector<bool> &visited, stack<long long> &answer, long long cur_vertex) {
    visited[cur_vertex] = 1;

    for(int vert: graph[cur_vertex]) {
        if(visited[vert] == 0) {
            DFS(graph, visited, answer, vert);

        }
    }
    answer.push(cur_vertex);
}


void topologicalSort(vector<vector<long long>> &graph, vector<bool> &visited, stack<long long> &answer, long long &n) {
    for(long long vert = 0; vert < n; vert++) {
        if(visited[vert] == 0) {
            DFS(graph, visited, answer, vert);
        }
    }

    
    long long mas[n], i = 0;
    while(!answer.empty()) {
        mas[answer.top()] = i+1;
        i++;
        answer.pop();
    }

    for(i = 0; i < n; i++) {
        cout << mas[i] << " ";
    }
}



int main() {
    long long allCount, pairCount, i;
    cin >> allCount >> pairCount;

    stack<long long> answer;
    vector<bool> visited(allCount, 0);
    vector<vector<long long>> graph(allCount, vector<long long>());

    for(i = 0; i < pairCount; i++) {
        long long el1, el2; cin >> el1 >> el2;
        graph[el1-1].push_back(el2-1);
    }

    topologicalSort(graph, visited, answer, allCount);
    return 0;
}