#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
    int a, b;
};


void DFS(int cur_vertex, vector<vector<int>> &graph, vector<bool> &visited, vector<int> &enter, vector<int> &ret, int &time, int parent, vector<Node> &answer) {
    visited[cur_vertex] = true;
    time++;
    enter[cur_vertex] = time;
    ret[cur_vertex] = time;


    for(int vert: graph[cur_vertex]) {
        if(vert == parent) {
            continue;
        }

        if(visited[vert] == true) {
            ret[cur_vertex]  = min(ret[cur_vertex], enter[vert]);
        }
        else {
            DFS(vert, graph, visited, enter, ret, time, cur_vertex, answer);


            ret[cur_vertex] = min(ret[cur_vertex], ret[vert]);

            if(ret[vert] > enter[cur_vertex]) {
                Node ans;
                if(cur_vertex < vert) {
                    ans.a = cur_vertex+1;
                    ans.b = vert+1;
                } else {
                    ans.a = vert+1;
                    ans.b = cur_vertex+1;
                }
                answer.push_back(ans);

            }
        }
    }
}


bool compareNodes(const Node &node1, const Node &node2) {
    if(node1.a == node2.a) {
        return node1.b < node2.b;
    }
    return node1.a < node2.a;
}


int main() {
    int n, m, i;
    cin >> n >> m;

    vector<bool> visited(n, false);
    vector<int> enter(n, -1);
    vector<int> ret(n, -1);
    vector<vector<int>> graph(n);
    int parent = -1;
    int time = 0;

    for (i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        graph[a - 1].push_back(b - 1);
        graph[b - 1].push_back(a - 1);
    }


    vector<Node> answer;
    for(i = 0; i < n; i++) {
        if(visited[i] == false) {
            DFS(i, graph, visited, enter, ret, time, parent, answer);
        }
    }


    sort(answer.begin(), answer.end(), compareNodes);


    for(i = 0; i < answer.size(); i++) {
        cout << answer[i].a << " " << answer[i].b << "\n";
    }
}
