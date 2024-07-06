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



long long Kruskal(vector<Node> &graph, long long &homeCount, long long &wayCount) {
    sort(graph.begin(), graph.end(), compareWeights);

    DSU dsu(homeCount);
    long long appendWay = wayCount - (wayCount - homeCount + 1);
    long long summa = 0, cur_way = 0;


    for(int i = 0; i < wayCount; i++) {
        if(cur_way < appendWay) {
            if(dsu.check_leader(graph[i].a-1) != dsu.check_leader(graph[i].b-1)) {
                dsu.unite(graph[i].a-1, graph[i].b-1);
                summa += graph[i].weight;
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
    long long homeCount, cityGoodCount, oxranaCityCount, i;
    cin >> homeCount >> cityGoodCount >> oxranaCityCount;

    long long all = cityGoodCount+oxranaCityCount;
    vector<Node> graphWay(cityGoodCount+oxranaCityCount);
    long long summaGood = 0;

    for(i = 0; i < cityGoodCount; i++) {
        cin >> graphWay[i].a >> graphWay[i].b >> graphWay[i].weight;
        summaGood += graphWay[i].weight;
    }


    for(i = cityGoodCount; i < all; i++) {
        cin >> graphWay[i].a >> graphWay[i].b >> graphWay[i].weight;
    }


    long long ans = Kruskal(graphWay, homeCount, all) - summaGood;
    if(ans < 0)
        cout << 0;
    else
        cout << ans;
    return 0;
}
