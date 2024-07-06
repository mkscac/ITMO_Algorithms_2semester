#include <iostream>
#include <string>
using namespace std;

int main() {
    int length, requestCount;
    string text;
    cin >> length >> requestCount;
    cin >> text;


    int countAns = 0, p, indGood, end;

    for(p = 0; p < requestCount; p++) {
        int a, b, l; cin >> a >> b >> l;
        a--; b--;
        end = a+l;
        indGood = 0;

        while(a < end) {
            if(text[a] != text[b])
                break;
            else
                indGood++;
            a++; b++;
        }
        
        if(indGood == l)
            countAns++;
    }

    cout << countAns;
    return 0;
}
