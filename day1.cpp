#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


int main() {
    ifstream file ("day1_input.txt");
    string line;
    std::vector<int> values;
    if (file.is_open()) {
        while (getline(file, line)) {
            values.push_back(std::stoi(line));
        }
        file.close();
    }

    // Part 1
    bool done = false;
    for (int x: values) {
        for (int y: values) {
            if (x + y == 2020) {
                std::cout << (x * y) << endl;
                done = true;
                break;
            }
        }
        if (done) break;
    }

    // Part 2
    done = false;
    for (int x: values) {
        for (int y: values) {
            for (int z: values) {
                if (x + y + z == 2020) {
                    std::cout << (x * y * z) << endl;
                    done = true;
                    break;
                }
            }
            if (done) break;
        }
        if (done) break;
    }
}