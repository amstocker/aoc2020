#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <map>
using namespace std;

class BagAmount {
    public:
        string name;
        int amount;
};


map<string, vector<string>> build_backrefs(map<string, vector<BagAmount>> const& bags) {
    map<string, vector<string>> backrefs;
    for (auto const& p: bags) {
        for (BagAmount b: p.second) {
            backrefs[b.name].push_back(p.first);
        }
    }
    return backrefs;
}

void build_paths_helper(int depth, string name, map<string, int>& paths, map<string, vector<string>> const& backrefs) {
    if (backrefs.find(name) != backrefs.end()) {
        for (string parent: backrefs.at(name)) {
            build_paths_helper(depth + 1, parent, paths, backrefs);
        }
    }
    if (depth > 0) paths[name] += 1;
}

map<string, int> build_paths(string name, map<string, vector<string>> const& backrefs) {
    map<string, int> paths;
    build_paths_helper(0, name, paths, backrefs);
    return paths;
}

int count_total_contained_helper(int depth, BagAmount bag, map<string, vector<BagAmount>> const& bags) {
    int partial_sum = 0;
    vector<BagAmount> bag_amounts = bags.at(bag.name);
    if (bag_amounts.size() == 0) {            
        return bag.amount;
    }
    for (BagAmount b: bag_amounts) {
        partial_sum += bag.amount * count_total_contained_helper(depth + 1, b, bags);
    }
    if (depth > 0) partial_sum += bag.amount;
    return partial_sum;
}

int count_total_contained(string name, map<string, vector<BagAmount>> const& bags) {
    BagAmount bag;
    bag.name = name;
    bag.amount = 1;
    return count_total_contained_helper(0, bag, bags);
}


int main() {
    ifstream file ("day7_input.txt");
    string line;

    regex container_pattern ("([a-z]+ [a-z]+) bags contain");
    regex bag_amount_pattern ("([0-9]+) ([a-z]+ [a-z]+) bag");
    smatch matches;

    string container;
    BagAmount bag_amount;
    vector<BagAmount> bag_amounts;
    map<string, vector<BagAmount>> bags;

    if (!file.is_open()) return 1;
    while (getline(file, line)) {
        regex_search(line, matches, container_pattern);
        container = matches[1];
        line = matches.suffix();
        while (regex_search(line, matches, bag_amount_pattern)) {
            bag_amount.amount = stoi(matches[1]);
            bag_amount.name = matches[2];
            line = matches.suffix();
            bag_amounts.push_back(bag_amount);
        }
        bags[container] = bag_amounts;
        bag_amounts.clear();
    }
    file.close();

    // Part 1
    map<string, vector<string>> backrefs = build_backrefs(bags);
    map<string, int> paths = build_paths("shiny gold", backrefs);
    cout << paths.size() << endl;

    // Part 2
    cout << count_total_contained("shiny gold", bags) << endl;
}