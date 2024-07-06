#include <iostream>
#include <vector>
#include <climits>
#include <queue>
using namespace std;


struct Node {
    int vert;
    int weight, price, flow;
    size_t back;
};


void relax(Node &v, int &vert, int &i, vector<bool> &visited, vector<int> &potentVert, vector<int> &distance, vector<int> &arr1, vector<int> &arr2, queue<int> &que) {
    if (distance[vert] + v.price + potentVert[vert] - potentVert[v.vert] < distance[v.vert]) {
        distance[v.vert] = distance[vert] + v.price + potentVert[vert] - potentVert[v.vert];
        arr1[v.vert] = vert;
        arr2[v.vert] = i;

        if(visited[v.vert] == 0) {
            que.push(v.vert);
            visited[v.vert] = 1;
        }
    }
}



void maxFlow_minCont(vector<vector<Node>> &graph, int &cityCount, int &s, int &t, int &ans_maxFlow, int &ans_minPrice) {
    int i;
    vector<int> potentVert(cityCount, 0);

    while(true) {
        vector<int> distance(cityCount, INT_MAX);
        vector<int> arr1(cityCount, 0);
        vector<int> arr2(cityCount, 0);
        vector<bool> visited(cityCount, 0);
        queue<int> que;

        distance[s] = 0;
        que.push(s);
        visited[s] = 1;

        while (!que.empty()) {
            int vert = que.front();
            que.pop();
            visited[vert] = 0;

            for (i = 0; i < graph[vert].size(); i++) {
                Node v = graph[vert][i];
                if (v.flow < v.weight) {
                    relax(v, vert, i, visited, potentVert, distance, arr1, arr2, que);
                }
            }
        }


        if(distance[t] == INT_MAX)
            break;

        for(i = 0; i < cityCount; i++) {
            if(distance[i] < INT_MAX)
                potentVert[i] += distance[i];
        }


        int fl = INT_MAX, v = t;
        while(v != s) {
            int u = arr1[v];
            Node &vert = graph[u][arr2[v]];
            fl = min(fl, vert.weight - vert.flow);
            v = u;
        }


        v = t;
        while (v != s) {
            int u = arr1[v];
            graph[u][arr2[v]].flow += fl;
            graph[v][graph[u][arr2[v]].back].flow -= fl;
            ans_minPrice += fl * graph[u][arr2[v]].price;
            v = u;
        }
        ans_maxFlow += fl;
    }
}



void pushVertex(vector<vector<Node>> &graph, int &a, int &b, int &weight, int &price) {
    Node buf1, buf2;
    buf1.vert = b;
    buf1.weight = weight;
    buf1.price = price;
    buf1.flow = 0;
    buf1.back = graph[b].size();
    graph[a].push_back(buf1);

    buf2.vert = a;
    buf2.weight = 0;
    buf2.price = -price;
    buf2.flow = 0;
    buf2.back = graph[a].size()-1;
    graph[b].push_back(buf2);
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int cityCount, wayCount, s, t, i;
    cin >> cityCount >> wayCount >> s >> t;

    vector<vector<Node>> graph(cityCount, vector<Node>());

    for(i = 0; i < wayCount; i++) {
        int a, b, weight, price;
        cin >> a >> b >> weight >> price;
        a--; b--;
        pushVertex(graph, a, b, weight, price);
    }

    int ans_maxFlow = 0, ans_minPrice = 0;
    s--; t--;
    maxFlow_minCont(graph, cityCount, s, t, ans_maxFlow, ans_minPrice);
    cout << ans_maxFlow << " " << ans_minPrice;
    return 0;
}
