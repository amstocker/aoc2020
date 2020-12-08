#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <map>
using namespace std;

const std::vector<string> required_fields = {
    "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"
};

const std::vector<string> optional_fields = {
    "cid"
};

const std::vector<string> eye_colors = {
    "amb", "blu", "brn", "gry", "grn", "hzl", "oth"
};


bool check_next_line(ifstream *file) {
    if (!file->is_open()) {
        return false;
    }
    string line;
    int pos = file->tellg();
    bool check;
    if (getline(*file, line)) {
        check = true;
    } else {
        check = false;
    }
    file->seekg(pos);
    return check;
}


bool is_valid(std::map<string, string> p) {
    bool valid = true;
    for (string field: required_fields) {
        if (p.find(field) == p.end()) {
            valid = false;
            break;
        }
    }
    return valid;
}

bool is_valid2(std::map<string, string> p) {
    std::regex hgt_pattern ("([0-9]+)(cm|in)");
    std::regex hcl_pattern ("(#[0-9a-f]{6})");
    std::regex pid_pattern ("([0-9]{9})");
    std::smatch matches;
    try {
        int byr = std::stoi(p["byr"]);
        int iyr = std::stoi(p["iyr"]);
        int eyr = std::stoi(p["eyr"]);
        string hgt = p["hgt"];
        string hcl = p["hcl"];
        string ecl = p["ecl"];
        string pid = p["pid"];
        bool ecl_valid = false;

        if (byr < 1920 || byr > 2002) return false;
        if (iyr < 2010 || iyr > 2020) return false;
        if (eyr < 2020 || eyr > 2030) return false;
        if (std::regex_search(hgt, matches, hgt_pattern)) {
            int h = std::stoi(matches[1]);
            if (hgt.size() != matches.str(0).size()) return false;
            if ((matches[2] == "cm") && (h < 150 || h > 193)) return false;
            if ((matches[2] == "in") && (h < 59 || h > 76)) return false;
        } else {
            return false;
        }
        if (!((hcl.size() == 7) && std::regex_search(hcl, matches, hcl_pattern))) return false;
        for (string cl: eye_colors) {
            if (ecl == cl) {
                ecl_valid = true;
                break;
            }
        }
        if (!ecl_valid) return false;
        if (!((pid.size() == 9) && std::regex_search(pid, matches, pid_pattern))) return false;
    } catch (const std::exception &e) {
        return false;
    }
    return true;
}


int main() {
    ifstream file ("day4_input.txt");
    std::vector<std::map<string, string>> passports;
    std::map<string, string> passport;
    string line;

    std::regex match_pattern ("([a-z]{3}):(\\S+)");
    std::smatch matches;

    bool found_one;
    if (file.is_open()) {
        while (getline(file, line)) {
            found_one = false;
            while (true) {
                if (!std::regex_search(line, matches, match_pattern)) {
                    break;
                }
                found_one = true;
                passport[matches[1]] = matches[2];
                line = matches.suffix();
            }
            if (!found_one || !check_next_line(&file)) {
                passports.push_back(passport);
                passport.clear();
            }
        }
        file.close();
    }

    // Part 1
    int valid_count = 0;
    for (std::map<string, string> p: passports) {
        if (is_valid(p)) valid_count++;
    }
    std::cout << valid_count << std::endl;

    // Part 2
    int valid_count2 = 0;
    for (std::map<string, string> p: passports) {
        if (is_valid2(p)) valid_count2++;
    }
    std::cout << valid_count2 << std::endl;
}