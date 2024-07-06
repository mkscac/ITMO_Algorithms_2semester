#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


struct NodeWay {
    long long a, b;
    long long weight;
};

struct NodeGraph {
    long long vertex;
    long long weight;
};


bool compareWeights(const NodeWay &node1, const NodeWay &node2) {
    return node1.weight < node2.weight;
}


class DSU {
public:
    vector<long long> parent;
    vector<long long> rank;

    DSU(long long n) {
        parent.resize(n);
        rank.resize(n, 1);
        for(long long i = 0; i < n; i++) {
            parent[i] = i;
        }
    }


    int check_leader(long long vert) {
        if(parent[vert] == vert)
            return vert;
        return parent[vert] = check_leader(parent[vert]);
    }


    void unite(long long vert1, long long vert2) {
        vert1 = check_leader(vert1), vert2 = check_leader(vert2);

        if(rank[vert1] > rank[vert2])
            swap(vert1, vert2);
        rank[vert2] += rank[vert1];
        parent[vert1] = vert2;
    }
};


void Kruskal(vector<NodeWay> &road, long long &homeCount, long long &wayCount, vector<vector<NodeGraph>> &graph) {
    sort(road.begin(), road.end(), compareWeights);

    DSU dsu(homeCount);
    long long appendWay = wayCount - (wayCount - homeCount + 1), cur_way = 0;
    NodeGraph buf;

    for(int i = 0; i < wayCount-1; i++) {
        if(cur_way < appendWay) {
            if(dsu.check_leader(road[i].a-1) != dsu.check_leader(road[i].b-1)) {
                dsu.unite(road[i].a-1, road[i].b-1);
                cur_way++;

                buf.vertex = road[i].b-1;
                buf.weight = road[i].weight;
                graph[road[i].a-1].push_back(buf);

                buf.vertex = road[i].a-1;
                graph[road[i].b-1].push_back(buf);
            }
        }
        else {
            break;
        }
    }
}


void DFS(long long x, long long parent, vector<long long> &a, vector<long long> &b, vector<long long> &c, vector<vector<NodeGraph>> &graph) {
    for(NodeGraph vert: graph[x]) {
        if(vert.vertex == parent)
            continue;
        DFS(vert.vertex, x, a, b, c, graph);
        a[x] = max(a[x], b[vert.vertex] + vert.weight - c[vert.vertex]);
        b[x] += c[vert.vertex];
    }
    a[x] += b[x];
    c[x] = max(a[x], b[x]);
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    long long vertexCount, wayCount, i;
    cin >> vertexCount >> wayCount;


    vector<NodeWay> graphWay(wayCount);
    vector<vector<NodeGraph>> graph(vertexCount);

    for(i = 0; i < wayCount; i++) {
        cin >> graphWay[i].a >> graphWay[i].b >> graphWay[i].weight;
    }


    Kruskal(graphWay, vertexCount, wayCount, graph);
    vector<long long> a(vertexCount, 0);
    vector<long long> b(vertexCount, 0);
    vector<long long> c(vertexCount, 0);

    DFS(0, -1, a, b, c, graph);
    cout << c[0];
    return 0;
}
