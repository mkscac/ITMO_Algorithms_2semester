#include <iostream>
#include <vector>
#include <queue>
using namespace std;



class Data {
public:
    vector<vector<int>> cats;
    vector<vector<int>> mans;
    queue<int> freeCats;
    vector<int> nextValue;
    vector<int> good4Man;
    vector<int> good4Cat;
};


void stableMatching1(Data &data, int &n) {
    int i, j;
    for (i = 0; i < n; ++i)
        data.freeCats.push(i);


    while(!data.freeCats.empty()) {
        int cat = data.freeCats.front();
        data.freeCats.pop();
        int man = data.cats[cat][data.nextValue[cat]++];

        if(data.good4Man[man] == -1) {
            data.good4Man[man] = cat;
            data.good4Cat[cat] = man;
        }
        else {
            int currentMatch = data.good4Man[man];
            if (data.mans[man][cat] < data.mans[man][currentMatch]) {
                data.good4Man[man] = cat;
                data.good4Cat[cat] = man;
                data.good4Cat[currentMatch] = -1;
                data.freeCats.push(currentMatch);
            }
            else {
                data.freeCats.push(cat);
            }
        }
    }
}


void resiseVector(Data &data, int &n) {
    data.cats.resize(n, vector<int>(n, 0));
    data.mans.resize(n, vector<int>(n, 0));
    data.nextValue.resize(n, 0);
    data.good4Cat.resize(n, -1);
    data.good4Man.resize(n, -1);
}


int main() {
    int n, i, j;
    cin >> n;

    Data data;
    resiseVector(data, n);


    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            cin >> data.cats[i][j];

    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            int ind; cin >> ind;
            data.mans[i][ind] = j;
        }
    }

    stableMatching1(data, n);
    for (i = 0; i < n; i++) {
        cout << i << " " << data.good4Cat[i] << "\n";
    }

    return 0;
}
