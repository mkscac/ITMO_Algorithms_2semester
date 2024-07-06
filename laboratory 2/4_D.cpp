#include <iostream>
#include <climits>
#include <limits>
#include <vector>
using namespace std;


void floydWarshall(vector<vector<unsigned long long>> &distanceGraph, int n) {
    int k, i, j;

    for(k = 0; k < n; k++) {
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                if(distanceGraph[i][k] != ULLONG_MAX && distanceGraph[k][j] != ULLONG_MAX)
                    distanceGraph[i][j] = min(distanceGraph[i][j], distanceGraph[i][k] + distanceGraph[k][j]);
            }
        }
    }
}



int main() {
    int n, wayCount, i, j;
    cin >> n >> wayCount;
    
    
    vector<vector<unsigned long long>> distanceGraph(n, vector<unsigned long long>(n));
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            if(i == j)
                distanceGraph[i][j] = 0;
            else
                distanceGraph[i][j] = ULLONG_MAX;
        }
    }


    for(i = 0; i < wayCount; i++) {
        unsigned long long start, end, weight;
        cin >> start >> end >> weight;

        weight = min(distanceGraph[start-1][end-1], weight);
        distanceGraph[start-1][end-1] = weight;
        distanceGraph[end-1][start-1] = weight;
    }

    floydWarshall(distanceGraph, n);


    unsigned long long minVertex = 0, minSumma = ULLONG_MAX;
    for(i = 0; i < n; i++) {
        unsigned long long summa = 0;
        for(j = 0; j < n; j++) {
            summa += distanceGraph[i][j];
            //cout << distanceGraph[i][j] << " ";
        }

        if(minSumma > summa) {
            minSumma = summa;
            minVertex = i;
        }
        //cout << "-- " << summa << "\n";
    }

    cout << minVertex+1;
    return 0;
}
