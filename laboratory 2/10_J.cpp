#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;


class DSU {
public:
    vector<int> parent;
    vector<int> rank;
    unordered_map<int, int> leader;

    DSU(int &n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            leader[i] = i;
        }
    }

    int check_leader(int vert) {
        if (parent[vert] == vert)
            return vert;
        else
            return parent[vert] = check_leader(parent[vert]);
    }

    void unite(int vert1, int vert2) {
        vert1 = check_leader(vert1), vert2 = check_leader(vert2);
        if (vert1 == vert2) return;

        if (rank[vert1] < rank[vert2])
            swap(vert1, vert2);

        parent[vert2] = vert1;
        rank[vert1] += rank[vert2];
        leader.erase(vert2);
    }
};


class Commands {
public:
    void commanda_delete(vector<vector<int>> &graph, int a, int b) {
        graph[a].erase(remove(graph[a].begin(), graph[a].end(), b), graph[a].end());
        graph[b].erase(remove(graph[b].begin(), graph[b].end(), a), graph[b].end());
    }

    void commanda_answer(DSU &dsu, vector<string> &answer, int vert1, int vert2) {
        if (dsu.check_leader(vert1) == dsu.check_leader(vert2))
            answer.emplace_back("YES");
        else
            answer.emplace_back("NO");
    }
};



int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int vertexCount, wayCount, requestCount, i, j;
    cin >> vertexCount >> wayCount >> requestCount;

    vector<vector<int>> graph(vertexCount);
    DSU dsu(vertexCount);
    Commands commandAll;

    int start, end;
    for (i = 0; i < wayCount; i++) {
        cin >> start >> end;
        graph[start-1].push_back(end-1);
        graph[end-1].push_back(start-1);
    }

    vector<int> numbers;
    vector<char> commands;
    vector<string> answer;
    char command;

    for (i = 0; i < requestCount; i++) {
        cin >> command >> start >> end;
        commands.push_back(command);
        numbers.push_back(start - 1);
        numbers.push_back(end - 1);

        if (command == '-') {
            commandAll.commanda_delete(graph, start - 1, end - 1);
        }
    }

    for (i = 0; i < graph.size(); i++) {
        for (j = 0; j < graph[i].size(); j++) {
            dsu.unite(i, graph[i][j]);
        }
    }

    int cur_V = numbers.size() - 1;
    for (i = requestCount - 1; i >= 0; i--) {
        int vert1 = numbers[cur_V-1], vert2 = numbers[cur_V];

        if(commands[i] == '?')
            commandAll.commanda_answer(dsu, answer, vert1, vert2);
        else
            dsu.unite(vert1, vert2);
        cur_V -= 2;
    }

    for (i = answer.size() - 1; i >= 0; i--) {
        cout << answer[i] << '\n';
    }
    return 0;
}
