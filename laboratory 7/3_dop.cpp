#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;
/// Подстроки +

bool check_substr(vector<string> &array_all_word, string &variant, int len) {
    set<string> sett_substr;
    string first = array_all_word[0];


    for(int i = 0; i <= first.size()-len; i++) {
        string part = first.substr(i, len);
        sett_substr.insert(part);
    }


    for(int i = 1; i < array_all_word.size(); i++) {
        set<string> curr_sett_substr;
        string curr = array_all_word[i];

        for(int j = 0; j <= curr.size()-len; j++) {
            string sub = curr.substr(j, len);
            if(sett_substr.find(sub) != sett_substr.end())
                curr_sett_substr.insert(sub);
        }

        sett_substr = curr_sett_substr;
        if(sett_substr.empty()) {
            return false;
        }
    }

    if (!sett_substr.empty()) {
        variant = *sett_substr.begin();
        return true;
    }
    return false;
}



string maxSubstr(int &countWord, vector<string> &array_all_word) {
    int left = 0, mid, right = array_all_word[0].size();

    for(int i = 1; i < countWord; i++) {
        right = min(right, (int)array_all_word[i].size());
    }

    string result;
    while(left <= right) {
        mid = (left + right) / 2;
        string variant;
        if (check_substr(array_all_word, variant, mid)) {
            result = variant;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return result;
}



int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int countWord, i;
    cin >> countWord;
    vector<string> array_all_word(countWord);

    for(i = 0; i < countWord; i++) {
        cin >> array_all_word[i];
    }

    cout << maxSubstr(countWord, array_all_word);
    return 0;
}




/*
3
abacaba
mycabarchive
acabaistrue

3
abcab
bcaba
ccab

8
abcab
afaffasdfsdfmkcmoeparpomrwfwopcspd
dskcmkwmxmawpeoawep
cmwexmwemoaew
cnwucnuiweb
bcweucwcai
urhokoiajc
aafhfuiheff
 */
