#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


void DFS_G(vector<vector<long long>> &graph, vector<bool> &visited, vector<long long> &time_processing, long long cur_vertex, long long &time) {
    visited[cur_vertex] = 1;


    for(int vert: graph[cur_vertex]) {
        if(visited[vert] == 0) {
            DFS_G(graph, visited, time_processing, vert, time);
        }
    }
    time_processing[time] = cur_vertex;
    time++;
}



void DFS_invert(vector<vector<long long>> &graph, vector<int> &components, vector<bool> &visited, long long cur_vertex, int comp) {
    components[cur_vertex] = comp;
    visited[cur_vertex] = 1;

    for(int vert: graph[cur_vertex]) {
        if(components[vert] == 0) {
            DFS_invert(graph, components, visited, vert, comp);
        }
    }
}



int main() {
    long long n, branchCount, requestCount, i;
    cin >> n >> branchCount >> requestCount;

    vector<bool> visited(n, false);
    vector<vector<long long>> graph(n, vector<long long>());
    vector<long long> time_processing(n, -1);
    vector<vector<long long>> graphInvert(n, vector<long long>());


    for(i = 0; i < branchCount; i++) {
        long long start, end;
        cin >> start >> end;
        graph[start-1].push_back(end-1);
        graphInvert[end-1].push_back(start-1);
    }

    long long time = 0;
    for(i = 0; i < n; i++) {
        if(visited[i] == 0) {
            DFS_G(graph, visited, time_processing, i, time);
        }
    }
//    for(i = n-1; i >= 0; i--) {
//        cout << i+1 << " " << time_processing[i]+1 << "\n";
//    }

    vector<int> components(n, 0);
    int comp = 1;
    visited.assign(n, false);
    for(i = n-1; i >= 0; i--) {
        if(visited[time_processing[i]] == 0) {
            DFS_invert(graphInvert, components, visited, time_processing[i], comp);
            comp++;
        }
    }

    
    for(i = 0; i < requestCount; i++) {
        long long start, end;
        cin >> start >> end;

        if(components[start-1] == components[end-1]) {
            cout << "YES\n";
        }
        else {
            cout << "NO\n";
        }
    }
    return 0;
}