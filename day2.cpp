#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
using namespace std;


struct data {
    int lower;
    int upper;
    char letter;
    string password;
};

bool is_valid(struct data x) {
    int count = 0;
    for (int i = 0; i < x.password.size(); i++) {
        if (x.password[i] == x.letter) {
            count++;
        }
    }
    if (count >= x.lower && count <= x.upper) {
        return true;
    }
    return false;
}

bool is_valid2(struct data x) {
    char a = x.password[x.lower - 1],
         b = x.password[x.upper - 1],
         c = x.letter;
    return ((a == c) || (b == c)) && (a != b);
}

int main() {
    ifstream file ("day2_input.txt");

    std::vector<data> parsed_lines;
    string line;
    struct data parsed;
    
    std::regex match_pattern("([0-9]+)-([0-9]+) ([a-z]): ([a-z]+)");
    std::smatch matches;

    if (file.is_open()) {
        while (getline(file, line)) {
            std::regex_search(line, matches, match_pattern);
            parsed = {
                std::stoi(matches.str(1)),
                std::stoi(matches.str(2)),
                matches.str(3)[0],
                matches.str(4)
            };
            parsed_lines.push_back(parsed);
        }
        file.close();
    }

    // Part 1
    int valid_count = 0;
    for (struct data x: parsed_lines) {
        if (is_valid(x)) {
            valid_count++;
        }
    }
    std::cout << valid_count << endl;

    // Part 2
    valid_count = 0;
    for (struct data x: parsed_lines) {
        if (is_valid2(x)) {
            valid_count++;
        }
    }
    std::cout << valid_count << endl;
}