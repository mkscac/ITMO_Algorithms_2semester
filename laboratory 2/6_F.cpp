#include <iostream>
#include <vector>
using namespace std;


struct Vertex {
    long long a;
    long long b ;
    long long weight;
};



int BellmanFord(vector<Vertex> &graph, vector<bool> &visited, vector<long long> &distance, vector<long long> &parent, long long src, long long V) {
    bool flag = true;
    int i, j;

    for(i = 1; i <= V; i++) {
        if(flag == false)
            break;

        flag = false;
        for(j = 0; j < graph.size(); j++) {
            if(distance[graph[j].a] + graph[j].weight < distance[graph[j].b]) { /// Relax
                flag = true;
                visited[graph[j].b] = 1;
                distance[graph[j].b] = distance[graph[j].a] + graph[j].weight;
                parent[graph[j].b] = graph[j].a;
            }
        }
    }


    int Circ = -1; /// наличие циклов с отрицательным весом
    for(i = 0; i < graph.size(); i++) {
        if(distance[graph[i].a] + graph[i].weight < distance[graph[i].b]) {
            Circ = graph[i].b;
            break;
        }
    }

    if(Circ != -1) {
        for(i = 0; i < V; i++)
            Circ = parent[Circ];

        long long len_cycle = 0;
        for(int v = Circ;; v = parent[v]) {
            len_cycle++;
            if(v == Circ && len_cycle > 1)
                break;
        }
        return len_cycle;
    }
    return -1;
}



int main() {
    long long mapCount, lengthMax, i, j;
    cin >> mapCount >> lengthMax;


    for (i = 0; i < mapCount; i++) {
        long long vertexCount, wayCount;
        cin >> vertexCount >> wayCount;


        vector<Vertex> graph;
        vector<bool> visited(vertexCount, false);
        vector<long long> distance(vertexCount, 0);
        vector<long long> parent(vertexCount, -1);


        for(j = 0; j < wayCount; j++) {
            long long a, b, weight;
            cin >> a >> b >> weight;
            Vertex vert;
            vert.a = a-1;
            vert.b = b-1;
            vert.weight = weight;
            graph.push_back(vert);
        }


        bool flag = false;
        for(int v = 0; v < vertexCount; v++) {
            int res = BellmanFord(graph, visited, distance, parent, v, vertexCount);
            if(res == -1 || res <= lengthMax) {
                flag = true;
                break;
            }
        }
        if(flag == true)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
    return 0;
}


/*
1 0
4 4
1 4 6
4 2 -14
2 1 4
2 3 6
 */

/*
2 4
4 4
1 4 6
4 2 -14
2 1 4
2 3 6
5 5
1 2 -5
2 3 -6
3 4 -5
4 5 10
5 1 4
*/
