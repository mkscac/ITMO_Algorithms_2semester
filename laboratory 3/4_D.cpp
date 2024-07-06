#include <iostream>
#include <vector>
#include <stack>
using namespace std;

void DFS(int cur_vertex, vector<vector<int>> &graph, vector<int> &visited, int &k) {
    visited[cur_vertex] = k;

    for(int U: graph[cur_vertex]) {
        if(visited[U] == 0) {
            DFS(U, graph, visited, k);
        }
    }
}


bool comp_chek(vector<vector<int>> &graph) {
    int cur_comp = 1;
    vector<int> componentsVis(graph.size(), 0);

    for(int i = 0; i < graph.size(); i++) {
        if(componentsVis[i] == 0) {
            DFS(i, graph, componentsVis, cur_comp);
            cur_comp++;
        }
    }

    if(cur_comp-1 == 1)
        return true;

    vector<int> mas(cur_comp-1 , 0);
    for(int i = 0; i < componentsVis.size(); i++) {
        mas[componentsVis[i]-1]++;
    }

    for(int i = 1; i < cur_comp-1; i++) {
        if(mas[i] > 1)
            return false;
    }
    return true;
}


bool deg_check(vector<vector<int>> &graph) {
    for(int i = 0; i < graph.size(); i++) {
        if(graph[i].size() % 2 != 0)
            return false;
    }
    return true;
}


void deleteWay(int &V, int &U, vector<vector<int>> &graph) {
    int n = graph.size();
    for(int i = 0; i < n; i++) {
        if(graph[V][i] == U) {
            graph[V].erase(graph[V].begin() + i);
            break;
        }
    }
    for(int i = 0; i < n; i++) {
        if(graph[U][i] == V) {
            graph[U].erase(graph[U].begin() + i);
            break;
        }
    }
}


void findEulerPath(int start, vector<vector<int>> &graph, vector<int> &answer) {
    stack<int> stack;
    stack.push(start);

    while(!stack.empty()) {
        int V = stack.top();

        bool found_edge = 0;
        for(int vert: graph[V]) {
            stack.push(vert);
            deleteWay(V, vert, graph);
            found_edge = 1;
            break;
        }

        if(found_edge == 0) {
            stack.pop();
            answer.push_back(V+1);
        }
    }
}



int main() {
    int homeCount, wayCount, i;
    cin >> homeCount >> wayCount;

    vector<vector<int>> graph(homeCount, vector<int>());

    for(i = 0; i < wayCount; i++) {
        int a, b; cin >> a >> b;
        graph[a-1].push_back(b-1);
        graph[b-1].push_back(a-1);
    }

    (comp_chek(graph));
    if((deg_check(graph) != 1) || (comp_chek(graph)) != 1) {
        cout << ":(";
        return 0;
    }

    vector<int> answer;
    findEulerPath(0, graph, answer);


    for(i = answer.size()-1; i >= 0; i--) {
        cout << answer[i] << " ";
    }
    return 0;
}
