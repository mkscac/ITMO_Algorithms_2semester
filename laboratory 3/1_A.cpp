#include <iostream>
#include <vector>
using namespace std;

void DFS(int cur_vertex, vector<vector<int>> &graph, vector<bool> &visited, vector<int> &predki) {
    visited[cur_vertex] = 1;

    for (int vert: graph[cur_vertex]) {
        if (visited[vert] == 0 && vert != predki[cur_vertex]) {
            predki[vert] = cur_vertex;
            DFS(vert, graph, visited, predki);
        }
    }
}



void Prufer(vector<vector<int>> &graph, vector<int> &answer, int &n) {
    vector<bool> visited(n, false);
    vector<int> predki(n, -1);
    vector<int> degreeVert(n, 0);

    predki[n-1] = -1;
    DFS(n-1, graph, visited, predki);

    int flag = -1;
    for(int i = 0; i < n; i++) {
        degreeVert[i] = (int)graph[i].size();
        if(degreeVert[i] == 1 && flag == -1)
            flag = i;
    }


    int cur_list = flag;
    for(int i = 0; i < n-2; i++) {
        int nextVert = predki[cur_list];
        answer.push_back(nextVert);
        degreeVert[nextVert]--;

        if(degreeVert[nextVert] == 1 && nextVert < flag) {
            cur_list = nextVert;
        }
        else {
            ++flag;
            while(flag < n && degreeVert[flag] != 1)
                ++flag;
            cur_list = flag;
        }
    }
}



int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int vertexCount, wayCount, i;
    cin >> vertexCount >> wayCount;

    vector<vector<int>> graph(vertexCount, vector<int>());
    for(i = 0; i < wayCount; i++) {
        int a, b; cin >> a >> b;
        graph[a-1].push_back(b-1);
        graph[b-1].push_back(a-1);
    }


    vector<int> answer;
    Prufer(graph, answer, vertexCount);

    for(i = 0; i < answer.size(); i++) {
        cout << answer[i]+1 << " ";
    }
    return 0;
}
