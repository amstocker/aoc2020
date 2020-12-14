#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;


int main() {
    ifstream file ("day13_input.txt");
    if (!file.is_open()) return 1;
    
    int t0;
    vector<int> bus_lines;
    
    string line;
    getline(file, line);
    t0 = stoi(line);

    string part;
    getline(file, line);
    stringstream ss (line);
    while (getline(ss, part, ',')) {
        if (part == "x") {
            bus_lines.push_back(1);
        } else {
            bus_lines.push_back(stoi(part));
        }
    }

    // Part 1
    int t = t0;
    bool found = false;
    while (!found) {
        for (int b: bus_lines) {
            if ((b > 1) && (t % b == 0)) {
                cout << (t - t0) * b << endl;
                found = true;
                break;
            }
        }
        t += 1;
    }

    // Part 2
    int m = 0, mi;
    for (int i = 0; i < bus_lines.size(); i++) {
        if (bus_lines[i] > m) {
            m = bus_lines[i];
            mi = i;
        }
    }

    t = m - mi;
    found = false;
    bool valid;
    int b;
    while (!found) {
        valid = true;
        for (int i = 0; i < bus_lines.size(); i++) {
            b = bus_lines[i];
            if ((t + i) % b != 0) {
                valid = false;
                break;
            }
        }
        t += m;
        if (!valid) continue;
        found = true;
        cout << t - m << endl;
    }
}