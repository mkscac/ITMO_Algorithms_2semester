#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

void findHamiltonCycle(vector<vector<int>> &graph, int &n, vector<int> &array) {
    for(int k = 0; k < n*(n-1); k++) {
        int V = array[0];
        int U = array[1];

        if(find(graph[V].begin(), graph[V].end(), U) != graph[V].end()) {
            array.erase(array.begin());
            array.push_back(V);
        }
        else {
            for(int i = 1; i < n-1; i++) {
                if(find(graph[0].begin(), graph[0].end(), array[i]) != graph[0].end() ||
                   find(graph[1].begin(), graph[1].end(), array[i+1]) != graph[1].end()) {
                    int it1 = 0, it2 = i;
                    while(1 + it1 < it2 - it1) {
                        swap(array[1+it1], array[i - it2]);
                        it1++; it2++;
                    }
                }
            }
        }
    }
}


int main() {
    int vertexCount, wayCount, i, j;
    cin >> vertexCount >> wayCount;

    vector<vector<int>> graph(vertexCount);
    vector<int> array;
    set<int> buf;

    for (i = 0; i < wayCount; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
        
        if(buf.find(a) == buf.end()) {
            buf.insert(a);
            array.push_back(a);
        }
        if(buf.find(b) == buf.end()) {
            buf.insert(b);
            array.push_back(b);
        }
    }
    
    findHamiltonCycle(graph, vertexCount, array);
    for(i = 0; i < vertexCount; i++) {
        cout << array[i] << " ";
    }
    return 0;
}
