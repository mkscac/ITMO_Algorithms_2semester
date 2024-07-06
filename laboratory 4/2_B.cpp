#include <iostream>
#include <vector>
#include <queue>
using namespace std;


bool BFS(vector<vector<int>> &graphMatrix, int &s, int &t, vector<int> &parent, vector<bool> &visited) {
    queue<int> que;
    que.push(s);
    parent[s] = -1;

    while(!que.empty()) {
        int V = que.front();
        que.pop();
        visited[V] = 1;

        for(int U = 0; U < graphMatrix.size(); U++) {
            if(visited[U] == 0 && graphMatrix[V][U] > 0) {
                if(U == t) {
                    parent[U] = V;
                    return true;
                }
                que.push(U);
                parent[U] = V;
                visited[U] = true;
            }
        }
    }
    return false;
}


int edmondsCarp(vector<vector<int>> &graphMatrix, int s, int t, int &size) {
    int U, V;
    vector<int> parent(size, 0);
    vector<bool> visited(size, 0);

    int maxFlow = 0;

    while(BFS(graphMatrix, s, t, parent, visited) == 1) {
        int cur_flow = INT_MAX;
        for(V = t; V != s; V = parent[V]) {
            U = parent[V];
            cur_flow = min(cur_flow, graphMatrix[U][V]);
        }


        for(V = t; V != s; V = parent[V]) {
            U = parent[V];
            graphMatrix[U][V] -= cur_flow;
            graphMatrix[V][U] += cur_flow;
        }
        maxFlow += cur_flow;
        fill(visited.begin(), visited.end(), false);
    }
    return maxFlow;
}



int main() {
    int starCount, wayCount, i, j;
    cin >> starCount >> wayCount;

    vector<vector<int>> graphMatrix(starCount, vector<int>(starCount));
    for(i = 0; i < starCount; i++) {
        for(j = 0; j < starCount; j++) {
            graphMatrix[i][j] = 0;
        }
    }


    for(i = 0; i < wayCount; i++) {
        int a, b, w; cin >> a >> b >> w;
        graphMatrix[a-1][b-1] = w;
    }
    
    cout << edmondsCarp(graphMatrix, 0, starCount-1, starCount);
}
