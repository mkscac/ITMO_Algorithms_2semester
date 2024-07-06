#include <iostream>
#include <vector>
using namespace std;



int main() {
    int vertexCount, i; cin >> vertexCount;

    vector<vector<int>> graph_1(vertexCount, vector<int>());
    vector<vector<int>> graph_2(vertexCount, vector<int>());


    for(i = 0; i < vertexCount-1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        graph_1[a].push_back(b);
        graph_1[b].push_back(a);
    }

    for(i = 0; i < vertexCount-1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        graph_2[a].push_back(b);
        graph_2[b].push_back(a);
    }




    vector<int> size_vertex_in_graph(vertexCount+1, 0);

    for(i = 0; i < vertexCount; i++) {
        size_vertex_in_graph[graph_1[i].size()] += 1;
        size_vertex_in_graph[graph_2[i].size()] += 1;
    }



    bool flag = true;
    for(i = 0; i < size_vertex_in_graph.size(); i++) {
        if(size_vertex_in_graph[i] % 2 != 0) {
            cout << "NO";
            flag = false;
            break;
        }
    }

    if(flag)
        cout << "YES";
    return 0;
}
