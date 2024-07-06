#include <iostream>
#include <vector>
#include <queue>
using namespace std;
/// минимальный разрез +

struct Node {
    int weight;
    int numberWay;
};


bool BFS(vector<vector<Node>> &graphMatrix, int &s, int &t, vector<int> &parent, vector<bool> &visited) {
    queue<int> que;
    que.push(s);
    parent[s] = -1;

    while(!que.empty()) {
        int V = que.front();
        que.pop();
        visited[V] = 1;

        for(int U = 0; U < graphMatrix.size(); U++) {
            if(visited[U] == 0 && graphMatrix[V][U].weight > 0) {
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


int fordFulkerson(vector<vector<Node>> &graphMatrix, int s, int t, int &size) {
    int U, V;
    vector<int> parent(size, 0);
    vector<bool> visited(size, 0);

    int maxFlow = 0;

    while(BFS(graphMatrix, s, t, parent, visited) == 1) {
        int cur_flow = INT_MAX;
        for(V = t; V != s; V = parent[V]) {
            U = parent[V];
            cur_flow = min(cur_flow, graphMatrix[U][V].weight);
        }


        for(V = t; V != s; V = parent[V]) {
            U = parent[V];
            graphMatrix[U][V].weight -= cur_flow;
            graphMatrix[V][U].weight += cur_flow;
        }
        maxFlow += cur_flow;
        fill(visited.begin(), visited.end(), false);
    }
    return maxFlow;
}



void BFS_for_cut(vector<vector<Node>> &graphMatrix, int s, int size, vector<bool> &visited) {
    queue<int> que;
    que.push(s);
    visited[s] = true;

    while (!que.empty()) {
        int V = que.front();
        que.pop();

        for (int U = 0; U < size; U++) {
            if (!visited[U] && graphMatrix[V][U].weight > 0) {
                que.push(U);
                visited[U] = true;
            }
        }
    }
}


void findMinCut(vector<vector<Node>> &graphMatrix, int s, int vertexCount, vector<int> &cutWay) {
    vector<bool> visited(vertexCount, false);
    BFS_for_cut(graphMatrix, s, vertexCount, visited);

    for(int i = 0; i < vertexCount; i++) {
        for(int j = 0; j < vertexCount; j++) {
            if (visited[i] && !visited[j] && graphMatrix[i][j].weight == 0 && graphMatrix[j][i].weight > 0)
                cutWay.push_back(graphMatrix[j][i].numberWay);
        }
    }
}



int main() {
    int vertexCount, wayCount, i;
    cin >> vertexCount >> wayCount;

    vector<vector<Node>> graphMatrix(vertexCount, vector<Node>(vertexCount));
    Node buf;
    for(i = 0; i < wayCount; i++) {
        int a, b, weight;
        cin >> a >> b >> weight;
        a--; b--;
        buf.weight = weight;
        buf.numberWay = i+1;
        graphMatrix[a][b] = buf;
        graphMatrix[b][a] = buf;
    }


    int maxFlow = fordFulkerson(graphMatrix, 0, vertexCount-1, vertexCount);

    vector<int> cutWay;
    findMinCut(graphMatrix, 0, vertexCount, cutWay);

    cout << cutWay.size() << " " << maxFlow << endl;
    for(i = 0; i < cutWay.size(); i++) {
        cout << cutWay[i] << " ";
    }
    return 0;
}


/*
3 3
1 2 3
1 3 5
3 2 7
 */

