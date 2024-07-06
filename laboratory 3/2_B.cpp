#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


struct Node {
    int a, b;
    int weight;
};


bool compareWeights(const Node& node1, const Node& node2) {
    return node1.weight < node2.weight;
}


void DFS(int cur_vertex, vector<vector<int>> &graph, vector<char> visited, vector<int> predki, bool &flag) {
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




int main() {
    int homeCount, wayCount, i;
    cin >> homeCount >> wayCount;


    Node road[wayCount];
    for(i = 0; i < wayCount; i++) {
        cin >> road[i].a >> road[i].b >> road[i].weight;
    }
    sort(road, road + wayCount, compareWeights);



    int appendWay = wayCount - (wayCount - homeCount + 1);
    int summa = 0, cur_way = 0;
    vector<vector<int>> graphMST(homeCount, vector<int>());

    vector<char> visited(homeCount, 'w');
    vector<int> predki(homeCount, 0);



    for(i = 0; i < wayCount; i++) {
        if(cur_way < appendWay) {
            bool flag = false;
            graphMST[road[i].a-1].push_back(road[i].b-1);
            graphMST[road[i].b-1].push_back(road[i].a-1);

            DFS(road[i].a-1, graphMST, visited, predki, flag);

            if(flag == false) {
                summa += road[i].weight;
                cur_way++;
            }
            else {
                graphMST[road[i].a-1].pop_back();
                graphMST[road[i].b-1].pop_back();
            }
        }

    }
    cout << summa;
    return 0;
}

