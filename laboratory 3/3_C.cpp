#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
    long long a, b;
    long long weight;
};


bool compareWeights(const Node& node1, const Node& node2) {
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



long long Kruskal(Node road[], long long &homeCount, long long &wayCount) {
    sort(road, road + wayCount, compareWeights);
    
    DSU dsu(homeCount);
    long long appendWay = wayCount - (wayCount - homeCount + 1);
    long long summa = 0, cur_way = 0;


    for(int i = 0; i < wayCount; i++) {
        if(cur_way < appendWay) {
            if(dsu.check_leader(road[i].a-1) != dsu.check_leader(road[i].b-1)) {
                dsu.unite(road[i].a-1, road[i].b-1);
                summa += road[i].weight;
                cur_way++;
            }
        }
        else {
            break;
        }
    }
    return summa;
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    long long homeCount, wayCount, i;
    cin >> homeCount >> wayCount;
    
    Node road[wayCount];
    for(i = 0; i < wayCount; i++) {
        cin >> road[i].a >> road[i].b >> road[i].weight;
    }
    
    cout << Kruskal(road, homeCount, wayCount);
    return 0;
}
