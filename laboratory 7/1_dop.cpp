#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node {
    int capacity, flow, from, to, a = -1, b = -1;
    Node(int cap, int fl, int from, int to,  int a, int b): capacity(cap), flow(fl), from(from),  to(to), a(a), b(b) {}
};


void addNode(vector<vector<Node>> &graph, int v, int u, long long capac, int x, int y) {
    Node buf1(capac, 0, v, u, x, y);
    graph[v].push_back(buf1);

    Node buf2(0, 0, u, v, x, y);
    graph[u].push_back(buf2);
}


int inNumberVertex(int i, int j, int &m) { return i*m + j; }
int outNumberVertex(int i, int j, int &n, int &m) { return i*m + n*m + j; }


bool BFS(vector<vector<Node>> &graph, vector<int> &parent, int &s, int &t) {
    fill(parent.begin(), parent.end(), -1);
    queue<int> que;
    que.push(s);

    while(!que.empty()) {
        int V = que.front();
        que.pop();

        for(int i = 0; i < graph[V].size(); i++) {
            Node &toVert = graph[V][i];

            if(parent[toVert.to] == -1 && toVert.flow < toVert.capacity) {
                parent[toVert.to] = V;
                if(toVert.to == t)
                    return true;
                que.push(toVert.to);
            }
        }
    }
    return false;
}


int fordFulkerson(vector<vector<Node>> &graph, vector<int> &parent, int &s, int &t) {
    int maxFlow = 0;

    while(BFS(graph, parent, s, t) == 1) {
        int cur_flow = INT_MAX;

        for(int V = t; V != s; V = parent[V]) {
            int u = parent[V];

            int ind = 0;
            while(graph[u][ind].to != V){
                ind++;
            }
            cur_flow = min(cur_flow, graph[u][ind].capacity - graph[u][ind].flow);
        }

        for(int V = t; V != s; V = parent[V]) {
            int U = parent[V];
            int ind = 0;
            while(graph[U][ind].to != V){
                ind++;
            }
            graph[U][ind].flow += cur_flow;

            ind = 0;
            while(graph[V][ind].to != U){
                ind++;
            }
            graph[V][ind].flow -= cur_flow;
        }
        maxFlow += cur_flow;
    }
    return maxFlow;
}



void BFS_for_cut(vector<vector<Node>> &graph, vector<bool> &visited, vector<int> &arrForWall, int &s) {
    queue<int> q;
    visited[s] = true;
    q.push(s);

    while(!q.empty()) {
        int U = q.front();
        q.pop();

        for(Node &e: graph[U]) {
            if(!visited[e.to] && e.flow < e.capacity) {
                q.push(e.to);
                visited[e.to] = true;
                arrForWall.push_back(e.to);
            }
        }
    }
}



void findMinCut(vector<vector<Node>> &graph, vector<vector<char>> &map, int s) {
    vector<int> arrForWall;
    vector<bool> visited(100*100, 0);
    BFS_for_cut(graph, visited, arrForWall, s);

    for(int v: arrForWall) {
        for(Node &e: graph[v]) {
            if(!visited[e.to] && e.capacity > 0 && e.flow == e.capacity)
                if(e.a != -1 && e.b != -1)
                    map[e.a][e.b] = '+';
        }
    }
}



int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m, i, j;
    cin >> n >> m;
    vector<vector<char>> map(100, vector<char>(100));
    vector<vector<Node>> graph(100 * 100);
    int s, t;

    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            if(i + 1 < n) {
                addNode(graph, outNumberVertex(i, j, n, m), inNumberVertex(i + 1, j, m), INT_MAX, -1, -1);
                addNode(graph, outNumberVertex(i + 1, j,n,m), inNumberVertex(i, j, m), INT_MAX, -1, -1);
            }
            if(j + 1 < m) {
                addNode(graph, outNumberVertex(i, j, n, m), inNumberVertex(i, j + 1, m), INT_MAX, -1, -1);
                addNode(graph, outNumberVertex(i, j + 1,n,m), inNumberVertex(i, j, m), INT_MAX, -1, -1);
            }
        }
    }


    int inVert, outVert;
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            cin >> map[i][j];
            inVert = inNumberVertex(i, j, m);
            outVert = outNumberVertex(i, j, n, m);

            if(map[i][j] == '#') {
                addNode(graph, inVert, outVert, 0, i, j);
            }
            else if (map[i][j] == '.') {
                addNode(graph, inVert, outVert, 1, i, j);
            }
            else if (map[i][j] == '-') {
                addNode(graph, inVert, outVert, INT_MAX, i, j);
            }
            else if (map[i][j] == 'A') {
                s = outVert;
            }
            else if (map[i][j] == 'B') {
                t = inVert;
            }
        }
    }


    vector<int> parent(100 * 100, -1);
    int maxFlow = fordFulkerson(graph, parent, s, t);
    findMinCut(graph, map, s);

    if(maxFlow >= INT_MAX)
        cout << -1;
    else {
        cout << maxFlow << "\n";

        for(i = 0; i < n; i++) {
            for(j = 0; j < m; j++) {
                cout << map[i][j];
            }
            cout << "\n";
        }
    }
    return 0;
}


/*
5 5
--...
A-.#-
.#.#-
--.--
--.-B
 */
