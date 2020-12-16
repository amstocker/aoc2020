#include <iostream>
#include <vector>
#include <map>
using namespace std;


int main() {
    vector<int> input {16, 12, 1, 0, 15, 7, 11};
    // vector<int> input {0, 3, 6};

    map<int, int> first;
    map<int, int> second;

    int turn, last, temp;
    for (turn = 0; turn < input.size(); turn++) {
        last = input[turn];
        first[last] = turn;
    }
    // Part 1
    // while (turn < 2020) {
    // Part 2
    while (turn < 30000000) {
        if (second.find(last) != second.end()) {
            last = second[last] - first[last];
        } else if (first.find(last) != first.end()) {
            last = 0;
        }
        if (second.find(last) != second.end()) {
            first[last] = second[last];
            second[last] = turn;
        } else if (first.find(last) != first.end()) {
            second[last] = turn;    
        } else {
            first[last] = turn;
        }
        turn++;
    }
    cout << last << endl;
}