#include <iostream>
#include <vector>
#include <set>
using namespace std;


void DFS_G(vector<vector<long long>> &graph, vector<bool> &visited, vector<long long> &time_processing, long long cur_vertex, long long &time) {
    visited[cur_vertex] = 1;

    for(long long vert: graph[cur_vertex]) {
        if(visited[vert] == 0) {
            DFS_G(graph, visited, time_processing, vert, time);
        }
    }
    time_processing[time] = cur_vertex;
    time++;
}



void DFS_invert(vector<vector<long long>> &graph, vector<long long> &components, vector<bool> &visited, long long cur_vertex, long long comp) {
    components[cur_vertex] = comp;
    visited[cur_vertex] = 1;

    for(long long vert: graph[cur_vertex]) {
        if(components[vert] == -1) {
            DFS_invert(graph, components, visited, vert, comp);
        }
    }
}


void Ans_Way_Components(vector<vector<long long>> &graph, vector<long long> &components, vector<long long> &minFamilyNumber, set<pair<int, int>> &answer) {
    for(long long i = 0; i < graph.size(); i++) {
        for(long long vert: graph[i]) {
            if(components[i] != components[vert]) {
                answer.emplace(minFamilyNumber[components[i]-1]+1, minFamilyNumber[components[vert]-1]+1);
            }
        }
    }
}



int main() {
    long long homeCount, wayCount, i;
    cin >> homeCount >> wayCount;

    vector<bool> visited(homeCount, false);
    vector<vector<long long>> graph(homeCount, vector<long long>());
    vector<long long> time_processing(homeCount, -1);
    vector<vector<long long>> graphInvert(homeCount, vector<long long>());


    for(i = 0; i < wayCount; i++) {
        long long start, end;
        cin >> start >> end;
        graph[start-1].push_back(end-1);
        graphInvert[end-1].push_back(start-1);
    }


    long long time = 0;
    for(i = 0; i < homeCount; i++) {
        if(visited[i] == 0) {
            DFS_G(graph, visited, time_processing, i, time);
        }
    }


    vector<long long> components(homeCount, -1);
    long long comp = 1;
    visited.assign(homeCount, false);
    for(i = homeCount-1; i >= 0; i--) {
        if(visited[time_processing[i]] == 0) {
            DFS_invert(graphInvert, components, visited, time_processing[i], comp);
            comp++;
        }
    }



    vector<long long> minFamilyNumber(comp-1, INT_MAX);
    for(i = 0; i < homeCount; i++) {
        minFamilyNumber[components[i]-1] = min(minFamilyNumber[components[i]-1], i);
    }


    visited.assign(homeCount, false);
    set<pair<int, int>> answer;
    Ans_Way_Components(graph, components, minFamilyNumber, answer);


    cout << comp-1 << " " << answer.size() << "\n";
    for(auto v: answer) {
        cout << v.first << " " << v.second << "\n";
    }
    return 0;
}
