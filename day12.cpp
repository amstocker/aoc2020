#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

enum Direction {
    N, S, E, W, L, R, F, ERR
};

class Instruction {
    public:
        Direction dir;
        int val;
};


Direction parse_direction(char c) {
    switch (c) {
        case 'N': return N;
        case 'S': return S;
        case 'E': return E;
        case 'W': return W;
        case 'L': return L;
        case 'R': return R;
        case 'F': return F;
    }
    return ERR;
}

void execute_instruction1(int& x, int& y, int& d, Instruction const& inst) {
    switch (inst.dir) {
        case N:
            y += inst.val;
            break;
        case S:
            y -= inst.val;
            break;
        case E:
            x += inst.val;
            break;
        case W:
            x -= inst.val;
            break;
        case L:
            d = (360 + d + inst.val) % 360;
            break;
        case R:
            d = (360 + d - inst.val) % 360;
            break;
        case F:
            switch (d / 90) {
                case 0:
                    x += inst.val;
                    break;
                case 1:
                    y += inst.val;
                    break;
                case 2:
                    x -= inst.val;
                    break;
                case 3:
                    y -= inst.val;
                    break;
            }
            break;
    }
}

void execute_instruction2(int& x, int& y, int& wx, int& wy, Instruction const& inst) {
    int tmp = wx;
    switch (inst.dir) {
        case N:
            wy += inst.val;
            break;
        case S:
            wy -= inst.val;
            break;
        case E:
            wx += inst.val;
            break;
        case W:
            wx -= inst.val;
            break;
        case L:
            switch (inst.val / 90) {
                case 0:
                    break;
                case 1:
                    wx = -wy;
                    wy = tmp;
                    break;
                case 2:
                    wx = -wx;
                    wy = -wy;
                    break;
                case 3:
                    wx = wy;
                    wy = -tmp;
                    break;
            }
            break;
        case R:
            switch (inst.val / 90) {
                case 0:
                    break;
                case 1:
                    wx = wy;
                    wy = -tmp;
                    break;
                case 2:
                    wx = -wx;
                    wy = -wy;
                    break;
                case 3:
                    wx = -wy;
                    wy = tmp;
                    break;
            }
            break;
        case F:
            x += inst.val * wx;
            y += inst.val * wy;
            break;
    }
}


int main() {
    ifstream file ("day12_input.txt");
    if (!file.is_open()) return 1;

    vector<Instruction> instructions;
    Instruction inst;
    string line;
    while (getline(file, line)) {
        inst.dir = parse_direction(line[0]);
        if (inst.dir == ERR) return 1;
        inst.val = stoi(line.substr(1));
        instructions.push_back(inst);
    }
    file.close();

    // Part 1
    int x = 0, y = 0, d = 0;
    for (Instruction inst: instructions) execute_instruction1(x, y, d, inst);
    cout << abs(x) + abs(y) << endl;

    // Part 2
    int wx = 10, wy = 1;
    x = 0;
    y = 0;
    for (Instruction inst: instructions) execute_instruction2(x, y, wx, wy, inst);
    cout << abs(x) + abs(y) << endl;
}