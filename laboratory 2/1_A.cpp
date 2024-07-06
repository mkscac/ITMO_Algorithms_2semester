#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int vertex;
    bool label = true;
};


bool DFS(vector<vector<Node>> &graph, vector<bool> &visited, int start, int end) {
    visited[start] = 1;

    if(start == end)
        return true;

    for(Node vert: graph[start]) {
        if(visited[vert.vertex] == 0 && vert.label == 1) {
//            if(vert.vertex == end)
//                return true;
            if(DFS(graph, visited, vert.vertex, end))
                return true;
        }
    }
    return false;
}



int main() {
    int n, m, q, i;
    cin >> n >> m >> q;


    vector<vector<Node>> graph(n);

    for(i = 0; i < m; i++) {
        long long a, b; cin >> a >> b;

        Node temp;
        temp.vertex = b-1;
        graph[a-1].push_back(temp);
        temp.vertex = a-1;
        graph[b-1].push_back(temp);
    }


    for(i = 0; i < q; i++) {
        char command; int a, b;
        cin >> command >> a >> b;


        if(command == '?') {
            vector<bool> visited(n, false);
            bool zn = DFS(graph, visited, a-1, b-1);

            if(zn == 1)
                cout << "YES" << "\n";
            else
                cout << "NO" << "\n";
        }

        else if(command == '-') {
            for(int j = 0; j < graph[a-1].size(); j++) {
                if(graph[a-1][j].vertex == b-1) {
                    graph[a-1][j].label = 0;
                    break;
                }
            }
            for(int j = 0; j < graph[b-1].size(); j++) {
                if(graph[b-1][j].vertex == a-1) {
                    graph[b-1][j].label = 0;
                    break;
                }
            }
        }
    }
    return 0;
}


