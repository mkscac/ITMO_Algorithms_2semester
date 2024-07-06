#include <iostream>
#include <vector>
#include <string>
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



int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    long long vertexCount, conditionCount, i;
    cin >> vertexCount >> conditionCount;


    vector<bool> visited(vertexCount*2, false);
    vector<vector<long long>> graph(vertexCount*2, vector<long long>());
    vector<long long> time_processing(vertexCount*2, -1);
    vector<vector<long long>> graphInvert(vertexCount*2, vector<long long>());


    for(i = 0; i < conditionCount; i++) {
        string condition, buf;
        cin >> buf;

        long long start = 0;
        long long end = 0;

        if(buf[0] == '!') {
            start = stoi(buf.substr(1, buf.size() - 1)) - 1;
            graph[start].push_back(start+vertexCount);

            graphInvert[start+vertexCount].push_back(start);
        }
        else {
            cin >> condition;
            start = stoi(buf) - 1;
            cin >> buf;
            end = stoi(buf) - 1;


            if(condition == "||") {
                graph[start+vertexCount].push_back(end);
                graph[end+vertexCount].push_back(start);

                graphInvert[end].push_back(start+vertexCount);
                graphInvert[start].push_back(end+vertexCount);
            }

            else if(condition == "->") {
                graph[start].push_back(end);
                graph[end+vertexCount].push_back(start+vertexCount);

                graphInvert[end].push_back(start);
                graphInvert[start+vertexCount].push_back(end+vertexCount);
            }

            else if(condition == "&") {
                graph[start+vertexCount].push_back(start);
                graph[end+vertexCount].push_back(end);

                graphInvert[start].push_back(start+vertexCount);
                graphInvert[end].push_back(end+vertexCount);
            }

            else if(condition == "^") {
                graph[start+vertexCount].push_back(end);
                graph[end+vertexCount].push_back(start);
                graph[start].push_back(end+vertexCount);
                graph[end].push_back(start+vertexCount);

                graphInvert[end].push_back(start+vertexCount);
                graphInvert[start].push_back(end+vertexCount);
                graphInvert[end+vertexCount].push_back(start);
                graphInvert[start+vertexCount].push_back(end);
            }
        }
    }


    long long time = 0;
    for(i = 0; i < vertexCount*2; i++) {
        if(visited[i] == 0) {
            DFS_G(graph, visited, time_processing, i, time);
        }
    }


    vector<long long> components(vertexCount*2, -1);
    long long comp = 1;
    visited.assign(vertexCount*2, false);
    for(i = vertexCount*2-1; i >= 0; i--) {
        if(visited[time_processing[i]] == 0) {
            DFS_invert(graphInvert, components, visited, time_processing[i], comp);
            comp++;
        }
    }



    bool flag = true;
    for(i = 0; i < vertexCount; i++) {
        if(components[i] == components[i+vertexCount]) {
            flag = false;
            break;
        }
    }

    if(flag == true) {
        cout << "YES";
    } else {
        cout << "NO";
    }
    return 0;
}
