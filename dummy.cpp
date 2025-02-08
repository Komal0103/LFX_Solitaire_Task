#include <iostream>
#include <bits/stdc++.h>
#include <vector>
// #include <map>

using namespace std;

enum colours {
    red,
    white,
    blue,
    navy_blue,
    yellow,
    pink,
    grey,
    green
};

// map<int, string> conversion;

int main() {
    vector<int> to_shuffle_array;
    unsigned seed = 8;
    for (int i=colours::red; i<=colours::green; i++) {
        to_shuffle_array.push_back(i);
    }
    shuffle(to_shuffle_array.begin(), to_shuffle_array.end(), default_random_engine(seed));
    for (int i=0; i<=colours::green; ++i) {
        cout << to_shuffle_array[i] <<" ";
    }
    cout<<endl;
    return 0;
}