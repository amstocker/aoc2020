#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;


bool check_next_line(ifstream& file) {
    if (!file.is_open()) {
        return false;
    }
    string line;
    int pos = file.tellg();
    bool check;
    if (getline(file, line)) {
        check = true;
    } else {
        check = false;
    }
    file.seekg(pos);
    return check;
}

std::vector<std::vector<std::string>> split_by_empty_line(ifstream& file) {
    std::vector<std::vector<std::string>> parts;
    std::vector<string> lines;
    std::string line;
    bool found_one = false;
    
    while(getline(file, line)) {
        if (!check_next_line(file)) {
            lines.push_back(line);
            parts.push_back(lines);
            break;
        }
        if ((line.size() == 0) && found_one) {
            parts.push_back(lines);
            lines.clear();
            found_one = false;
            continue;
        }
        found_one = true;
        lines.push_back(line);
    }
    return parts;
}


std::map<char, int> process_answers(std::vector<std::string> answers) {
    std::map<char, int> counts;
    for (std::string line: answers) {
        for (char c: line) {
            if (counts.find(c) != counts.end()) {
                counts[c] += 1;
            } else {
                counts[c] = 1;
            }
        }
    }
    return counts;
}

int count_all(int n, std::map<char, int> answers) {
    int count = 0;
    for (auto const& i: answers) {
        if (i.second == n) count++;
    }
    return count;
}


int main() {
    ifstream file ("day6_input.txt");
    if (!file.is_open()) return 1;

    std::vector<std::vector<string>> parts = split_by_empty_line(file);
    file.close();

    // Part 1
    int total = 0;
    for (std::vector<std::string> part: parts) {
        total += process_answers(part).size();
    }
    std::cout << total << std::endl;

    // Part 2
    int total2 = 0;
    for (std::vector<std::string> part: parts) {
        total2 += count_all(part.size(), process_answers(part));
    }
    std::cout << total2 << std::endl;
}