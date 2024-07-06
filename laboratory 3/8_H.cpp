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
    int islandCount, courseCount, numberOstov, cours, j;
    cin >> islandCount >> courseCount >> numberOstov;


    vector<vector<Node>> graph(islandCount);
    for(cours = 0; cours < courseCount; cours++) {
        int n, time;
        cin >> n >> time;


        Node numbVert[n];
        for(j = 0; j < n; j++) {
            int vert; cin >> vert;
            numbVert[j].vert = vert-1;
            numbVert[j].weight = time;
        }

        for(j = 0; j < n-1; j++) {
            int ind = j+1;
            while(ind < n) {
                graph[numbVert[j].vert].push_back(numbVert[ind]);
                graph[numbVert[ind].vert].push_back(numbVert[j]);
                ind++;
            }
        }
    }


    vector<bool> visited(islandCount, false);
    vector<int> distance(islandCount, INT_MAX);

    deikstra(0, graph, visited, distance);
    if(distance[numberOstov-1] != INT_MAX) {
        cout << distance[numberOstov-1];
    } else {
        cout << -1;
    }
    return 0;
}
