#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;


long int arrangements_helper (int d, int i, map<int, long int>& arrangement_counts, vector<int> const& data) {
    int j;
    long int arrangements;
    if (arrangement_counts.find(i) != arrangement_counts.end()) {
        return arrangement_counts.at(i);
    } else {
        j = i - 1;
        arrangements = 0;
        while ((j >= 0) && ((data[i] - data[j]) <= 3)) {
            arrangements += arrangements_helper(d + 1, j, arrangement_counts, data);
            j--;
        }
    }
    arrangement_counts[i] = arrangements;
    return arrangements;
}

long int count_arrangements(vector<int> const& data) {
    map<int, long int> arrangement_counts;
    arrangement_counts[0] = 1;
    
    return arrangements_helper(0, data.size() - 1, arrangement_counts, data);
}


int main() {
    ifstream file ("day10_input.txt");
    string line;
    vector<int> data;

    if (!file.is_open()) return 1;
    while (getline(file, line)) {
        data.push_back(stoi(line));
    }
    file.close();
    
    data.push_back(0);
    sort(data.begin(), data.end());
    data.push_back(data[data.size() - 1] + 3);

    // Part 1
    int diff1 = 0, diff3 = 0;
    for (int i = 1; i < data.size(); i++) {
        if      (data[i] - data[i - 1] == 1) diff1++;
        else if (data[i] - data[i - 1] == 3) diff3++;
    }
    cout << diff1 * diff3 << endl;

    // Part 2
    //      (Doesn't actually work if input is too large...)
    cout << count_arrangements(data) << endl;
}