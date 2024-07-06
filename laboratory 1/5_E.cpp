#include <iostream>
#include <vector>
using namespace std;


void DFS(long long cur_vertex, vector<vector<long long>> &graph, vector<char> &visited, vector<long long> &predki, bool &flag) {
    visited[cur_vertex] = 'g';


    for(int U: graph[cur_vertex]) {
        if(visited[U] == 'w') {
            predki[U] = cur_vertex;
            DFS(U, graph, visited, predki, flag);
        }

        if(visited[U] == 'g' && predki[cur_vertex] != U) {
            flag = true;
            break;
        }
    }
    visited[cur_vertex] = 'b';
}



void answer(vector<vector<long long>> &graph, vector<char> &visited, vector<long long> &predki) {
    bool flag = false;

    for(int V = 0; V < visited.size(); V++) {
        if(visited[V] == 'w') {
            DFS(V, graph, visited, predki, flag);
        }
    }


    if(flag == true)
        cout << "YES";
    else
        cout << "NO";
    
}



int main() {
    long long countPoint = 0, countRoad = 0, i = 0;
    cin >> countPoint >> countRoad;


    vector<char> visited(countPoint, 'w');
    vector<vector<long long>> graph(countPoint, vector<long long>());
    vector<long long> predki(countPoint, 0);

    for(i = 0; i < countRoad; i++) {
        long long el1, el2; cin >> el1 >> el2;
        graph[el1-1].push_back(el2-1);
        graph[el2-1].push_back(el1-1);
    }


    answer(graph, visited, predki);
}
