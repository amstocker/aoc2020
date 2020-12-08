#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
using namespace std;

int main() {
    std::vector<std::tuple<int, int>> slopes = make_slopes();

    for (std::tuple<int, int> slope: slopes) {
        std::cout << std::get<0>(slope) << ' ' << std::get<1>(slope) << endl;
    }
}