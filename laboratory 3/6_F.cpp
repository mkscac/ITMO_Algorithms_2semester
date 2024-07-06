#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
    int a, b;
    int weight;
    bool flagDeleteWay = false;
};


bool compareWeights(const Node &node1, const Node &node2) {
    return node1.weight < node2.weight;
}


class DSU {
public:
    vector<int> parent;
    vector<int> rank;

    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 1);
        for(int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }


    int check_leader(int vert) {
        if(parent[vert] == vert)
            return vert;
        return parent[vert] = check_leader(parent[vert]);
    }


    void unite(int vert1, int vert2) {
        vert1 = check_leader(vert1), vert2 = check_leader(vert2);

        if(rank[vert1] > rank[vert2])
            swap(vert1, vert2);
        rank[vert2] += rank[vert1];
        parent[vert1] = vert2;
    }
};



int Kruskal_1_MST(Node road[], int &homeCount, int &wayCount) {
    DSU dsu(homeCount);
    int appendWay = wayCount - (wayCount - homeCount + 1);
    int summa_way_MST = 0, cur_way = 0;


    for(int i = 0; i < wayCount; i++) {
        if(cur_way < appendWay) {
            if(dsu.check_leader(road[i].a-1) != dsu.check_leader(road[i].b-1)) {
                dsu.unite(road[i].a-1, road[i].b-1);
                summa_way_MST += road[i].weight;
                cur_way++;
            }
        }
        else
            break;
    }
    return summa_way_MST;
}


int Kruskal_2_MST(Node road[], int &homeCount, int &wayCount, int summa1_MST) {
    int summa_way_MST_2_min = INT_MAX;
    Node road2[wayCount-1];

    for(int i = 0; i < wayCount/2; i++) {
        int ind = 0;
        for (int j = 0; j < wayCount; j++) {
            if (road[j].weight != road[i].weight)
                road2[ind++] = road[j];
        }

        int summaNew = Kruskal_1_MST(road2, homeCount, wayCount);
        if (summaNew != summa1_MST)
            summa_way_MST_2_min = min(summa_way_MST_2_min, summaNew);

        road[i].flagDeleteWay = true;
    }
    return summa_way_MST_2_min;
}



int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int homeCount, wayCount, i;
    cin >> homeCount >> wayCount;

    Node road[wayCount];
    for(i = 0; i < wayCount; i++) {
        cin >> road[i].a >> road[i].b >> road[i].weight;
    }
    sort(road, road + wayCount, compareWeights);


    int summa1MST = Kruskal_1_MST(road, homeCount, wayCount);
    cout << summa1MST << " " << Kruskal_2_MST(road, homeCount, wayCount, summa1MST);
    return 0;
}
