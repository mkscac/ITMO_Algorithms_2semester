#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int vert;
    int weight;
};


void deikstra(int start, vector<vector<Node>> &graph, vector<bool> &visited, vector<int> &distance) {
    distance[start] = 0;

    for(int i = 0; i < graph.size(); i++) {

        int vertex = -1;
        for(int v = 0; v < graph.size(); v++) {
            if(visited[v] == 0 && (distance[vertex] > distance[v] || vertex == -1)) {
                vertex = v;
            }
        }
        if(distance[vertex] == INT_MAX) {
            break;
        }
        visited[vertex] = true;

        for(Node vi: graph[vertex]) {
            if(distance[vi.vert] > distance[vertex] + vi.weight && visited[vi.vert] == false) { /// Relax
                distance[vi.vert] = distance[vertex] + vi.weight;
            }
        }
    }
}



int main() {
    int n, wayCount, i;
    cin >> n >> wayCount;

    vector<vector<Node>> graph(n);
    vector<bool> visited(n, false);
    vector<int> distance(n, INT_MAX);

    for(i = 0; i < wayCount; i++) {
        int start, end, weight;
        cin >> start >> end >> weight;
        Node temp;
        temp.vert = end-1; temp.weight = weight;
        graph[start-1].push_back(temp);
    }


    deikstra(0, graph, visited, distance);
    if(distance[n-1] != INT_MAX) {
        cout << distance[n-1];
    } else {
        cout << -1;
    }
    return 0;
}
