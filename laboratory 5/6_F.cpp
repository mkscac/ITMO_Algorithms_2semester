#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Kukushka_algorithm {
public:
    vector<string> people_1;
    vector<string> people_2;
    vector<string> people_3;
    int sizeTable;

    Kukushka_algorithm() {
        sizeTable = 1000003;
        people_1.resize(sizeTable, "");
        people_2.resize(sizeTable, "");
        people_3.resize(sizeTable, "");
    }



    int hash_fun_1(string &element) {
        long long zn = 0;

        for(int i = 0; i < element.size(); i++)
            zn += element[i] + (zn * 228);

        return (zn % sizeTable);
    }


    int hash_fun_2(string &element) {
        long long zn = 0;

        for(int i = 0; i < element.size(); i++)
            zn += element[i] + (zn * 228);

        return (zn + 123) % (sizeTable);
    }



    void insert(string &element, vector<string> &people_n) {
        int ind_hash_1 = hash_fun_1(element);

        if(people_n[ind_hash_1] == "") {
            people_n[ind_hash_1] = element;
        }
        else {
            int ind_hash_2 = hash_fun_2(element);
            people_n[ind_hash_2] = element;
        }
    }



    bool find_element(vector<string> &people_n, string &element) {
//        int ind_1 = hash_fun_1(element);
//        int ind_2 = hash_fun_2(element);
        return (people_n[hash_fun_1(element)] == element) || (people_n[hash_fun_2(element)] == element);
    }

};




int main() {
    int n, i;
    cin >> n;

    Kukushka_algorithm algo;

    vector<string> key_1(n);
    vector<string> key_2(n);
    vector<string> key_3(n);

    vector<int> points(3, 0);


    for(i = 0; i < n; i++) {
        cin >> key_1[i];
        algo.insert(key_1[i], algo.people_1);
    }


    for(i = 0; i < n; i++) {
        cin >> key_2[i];
        algo.insert(key_2[i], algo.people_2);
    }


    for(i = 0; i < n; i++) {
        cin >> key_3[i];
        algo.insert(key_3[i], algo.people_3);
    }





    for(i = 0; i < n; i++) {
        if(!algo.find_element(algo.people_2, key_1[i]) && !algo.find_element(algo.people_3, key_1[i]))
            points[0] += 3;

        else if(algo.find_element(algo.people_2, key_1[i]) && algo.find_element(algo.people_3, key_1[i]))
            points[0] += 0;

        else
            points[0] += 1;
    }


    for(i = 0; i < n; i++) {
        if(!algo.find_element(algo.people_1, key_2[i]) && !algo.find_element(algo.people_3, key_2[i]))
            points[1] += 3;

        else if(algo.find_element(algo.people_1, key_2[i]) && algo.find_element(algo.people_3, key_2[i]))
            points[1] += 0;

        else
            points[1] += 1;
    }


    for(i = 0; i < n; i++) {
        if(!algo.find_element(algo.people_1, key_3[i]) && !algo.find_element(algo.people_2, key_3[i]))
            points[2] += 3;

        else if(algo.find_element(algo.people_1, key_3[i]) && algo.find_element(algo.people_2, key_3[i]))
            points[2] += 0;

        else
            points[2] += 1;
    }



    for(i = 0; i < 3; i++)
        cout << points[i] << " ";

    return 0;
}


