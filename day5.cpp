#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;


std::tuple<int, int> code_to_seat(std::string code) {
    int row = 0;
    int column = 0;
    for (int i = 0; i < 7; i++) {
        if (code[i] == 'B') row += (1 << (6 - i));
    }
    for (int i = 0; i < 3; i++) {
        if (code[7 + i] == 'R') column += (1 << (2 - i));
    }
    return {row, column};
}

int seat_to_id(std::tuple<int, int> seat) {
    return (std::get<0>(seat) * 8) + std::get<1>(seat); 
}

int max_seat_id(std::vector<std::tuple<int, int>> seats) {
    int id;
    int max_id = 0;
    for (std::tuple<int, int> seat: seats) {
        id = seat_to_id(seat);
        if (id > max_id) {
            max_id = id;
        }
    }
    return max_id;
}

int comparator(std::tuple<int, int> a, std::tuple<int, int> b) {
    int a_id = seat_to_id(a);
    int b_id = seat_to_id(b);
    return a_id < b_id;
}


int main() {
    ifstream file ("day5_input.txt");
    std::vector<std::tuple<int, int>> seats;
    
    std::string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            seats.push_back(code_to_seat(line));
        }
    }
    std::sort(seats.begin(), seats.end(), comparator);

    // Part 1
    int max_id = seat_to_id(seats[seats.size() - 1]);
    std::cout << max_id << std::endl;

    // Part 2
    int i = seat_to_id(seats[0]);
    for (std::tuple<int, int> seat: seats) {
        if (i != seat_to_id(seat)) {
            std::cout << seat_to_id(seat) - 1 << std::endl;
            i++;
        }
        i++;
    }
}