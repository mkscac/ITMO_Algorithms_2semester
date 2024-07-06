#include <iostream>
#include <vector>
using namespace std;


struct Node {
    int vert;
    bool free = true;
};


void buildDwudolnGraph(vector<vector<Node>> &graph, int &N, int &M) {
    int i, j;
    Node buf;

    for(i = 0; i < N; i++) {
        for(j = 0; j < M; j++) {
            if((i+j) % 2 == 0) {
                int cur_vertex = i * M + j;

                if (i > 0) {
                    buf.vert = cur_vertex - M;
                    graph[cur_vertex].push_back(buf);
                }
                if (i < N - 1) {
                    buf.vert = cur_vertex + M;
                    graph[cur_vertex].push_back(buf);
                }
                if (j > 0) {
                    buf.vert = cur_vertex - 1;
                    graph[cur_vertex].push_back(buf);
                }
                if (j < M - 1) {
                    buf.vert = cur_vertex + 1;
                    graph[cur_vertex].push_back(buf);
                }
            }
        }
    }
}


int numderVertex(int &M, int &a, int &b) {
    return a * M + b;
}


void closeVertex(vector<vector<Node>> &graph, int &closeVert) {
    int i, j;

    if(graph[closeVert].size() > 0) {
        for(j = 0; j < graph[closeVert].size(); j++) {
            graph[closeVert][j].free = false;
        }
    }
    else {
        for(i = 0; i < graph.size(); i++) {
            for(j = 0; j < graph[i].size(); j++) {
                if(graph[i][j].vert == closeVert) {
                    graph[i][j].free = false;
                }
            }
        }
    }
}


bool DFS(vector<vector<Node>> &graph, vector<bool> &visited, vector<long long> &mt, long long cur_vertex) {
    if(visited[cur_vertex] == 1) {
        return false;
    }
    visited[cur_vertex] = 1;

    for(Node v: graph[cur_vertex]) {
        if (v.free == 1 && (mt[v.vert] == -1 || DFS(graph, visited, mt, mt[v.vert])) == 1) {
            mt[v.vert] = cur_vertex;
            return true;
        }
    }
    return false;
}



int main() {
    int N, M; cin >> N >> M;
    int Q; cin >> Q;
    int i;



    vector<vector<Node>> graph(M*N, vector<Node>());
    buildDwudolnGraph(graph, N, M);


    for(i = 0; i < Q; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        int vert = numderVertex(M, a, b);
        closeVertex(graph, vert);
        //cout << a << " " << b << " " << vert << "\n";
    }



    vector<long long> mt(N*M, -1); // с какой вершиной сматчена вершина правой доли (-1, если ни с какой)

    int cnt = 0;
    for(i = 0; i < N*M; i++) {
        if(graph[i].size() > 0) {
            vector<bool> visited(N*M, 0);
            if(DFS(graph, visited, mt, i))
                cnt++;
        }
    }

    cout << cnt*2;
    return 0;
}
