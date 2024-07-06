#include <iostream>
#include <vector>
#include <queue>
using namespace std;


void BFS(vector<vector<long long>> &graph, vector<bool> &visited, vector<long long> &distance, long long cur_vertex) {
    queue<long long> que;
    que.push(cur_vertex);
    distance[cur_vertex] = 0;

    while(!que.empty()) {
        long long V_first = que.front();
        que.pop();
        visited[V_first] = 1;

        for(long long vert: graph[V_first]) {
            if((distance[vert] > distance[V_first] + 1) && (visited[vert] == 0)) {
                distance[vert] = distance[V_first] + 1;
                que.push(vert);
            }
        }
    }
}



int main() {
    long long n, pairCount, daysCount, i = 0;
    cin >> n;
    cin >> pairCount >> daysCount;


    vector<bool> visited(n, false);
    vector<vector<long long>> graph(n, vector<long long>());
    vector<long long> distance(n, INT_MAX);

    for (i = 0; i < pairCount; i++) {
        long long el1, el2;
        cin >> el1 >> el2;
        graph[el1 - 1].push_back(el2 - 1);
        graph[el2 - 1].push_back(el1 - 1);
    }

    BFS(graph, visited, distance, 0);


    bool flag = false;
    for(i = 0; i < n; i++) {
        if(distance[i] == daysCount) {
            cout << i + 1 << "\n";
            flag = true;
        }
    }
    if(flag == false) {
        cout << "NO";
    }
}
