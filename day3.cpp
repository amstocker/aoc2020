#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


int traverse(std::vector<string> *lines, int dx, int dy) {
    int w = lines->at(0).size(),
        h = lines->size(),
        posx = 0,
        posy = 0,
        count = 0;
    while (posy < h) {
        if (lines->at(posy)[posx % w] == '#') count++;
        posx += dx;
        posy += dy;
    };
    return count;
}

int main() {
    ifstream file ("day3_input.txt");
    string line;
    std::vector<string> lines;

    if (file.is_open()) {
        while (getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    }
    
    // Part 1
    std::cout << traverse(&lines, 3, 1) << endl;

    // Part 2
    std::cout << traverse(&lines, 1, 1) *
                 traverse(&lines, 3, 1) *
                 traverse(&lines, 5, 1) *
                 traverse(&lines, 7, 1) *
                 traverse(&lines, 1, 2) << endl;
}