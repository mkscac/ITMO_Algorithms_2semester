#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    int i, j;
    string text, name;
    cin >> text >> name;

    int count = 0;
    vector<int> index;

    for(i = 0; i < text.size()-name.size()+1; i++) {
        int k = 0;
        int ind = i;
        for(j = 0; j < name.size(); j++) {
            if(text[ind] == name[j]) {
                k++;
                ind++;
            } else {
                break;
            }
        }
        if(k == name.size()) {
            index.push_back(i);
            count++;
        }
    }

    cout << count << "\n";

    for(i = 0; i < index.size(); i++) {
        cout << index[i] << " ";
    }

    return 0;
}
