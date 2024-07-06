#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct myGalaxy {
    vector<long long> zvezd;
    priority_queue<long long, vector<long long>, greater<long long>> minHeap;
    priority_queue<long long> maxHeap;
};


void addStar(myGalaxy &star, long long v) {
    if (star.maxHeap.empty() || v <= star.maxHeap.top()) {
        star.maxHeap.push(v);
    } else {
        star.minHeap.push(v);
    }

    if (star.maxHeap.size() > star.minHeap.size()) {
        star.minHeap.push(star.maxHeap.top());
        star.maxHeap.pop();
    }
    if(star.maxHeap.size() < star.minHeap.size()) {
        star.maxHeap.push(star.minHeap.top());
        star.minHeap.pop();
    }
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
        else
            return check_leader(parent[vert]);
    }


    void unite(long long vert1, long long vert2, vector<myGalaxy> &galactic) { /// объединение двух множеств
        vert1 = check_leader(vert1), vert2 = check_leader(vert2);
        if (rank[vert1] > rank[vert2])
            swap(vert1, vert2);
        rank[vert2] += rank[vert1];
        parent[vert1] = vert2;


        for(long long v: galactic[vert1].zvezd) {
            galactic[vert2].zvezd.push_back(v);
            addStar(galactic[vert2], v);
        }
    }


    int mediana(priority_queue<long long> &maxHeap) {
        return maxHeap.top();
    }
};




int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    long long vertexCount, requestCount, i;
    cin >> vertexCount >> requestCount;

    DSU dsu(vertexCount);
    vector<myGalaxy> galactic;

    for(i = 0; i < vertexCount; i++) {
        myGalaxy Gal;
        Gal.maxHeap.push(i);
        Gal.zvezd.push_back(i);
        galactic.push_back(Gal);
    }



    for(i = 0; i < requestCount; i++) {
        int type;
        cin >> type;

        if(type == 1) {
            long long a, b;
            cin >> a >> b;
            if(dsu.check_leader(galactic[a - 1].zvezd[0]) != dsu.check_leader(galactic[b - 1].zvezd[0]))
                dsu.unite(a - 1, b - 1, galactic);
        }

        else {
            long long vert;
            cin >> vert;
            long long cur_leader = dsu.check_leader(galactic[vert - 1].zvezd[0]);
            cout << dsu.mediana(galactic[cur_leader].maxHeap) + 1 << "\n";
        }
    }
    return 0;
}
