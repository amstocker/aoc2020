#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


class SeatMap {
    public:
        vector<string> grid, original_grid;
        int w, h;
        int occupied;
        bool changed_state;

        char (*permute_seat)(int, int, vector<string> const&);


        bool load_from_file(string filename) {
            ifstream file (filename);
            if (!file.is_open()) return false;

            grid.clear();
            string line;
            while (getline(file, line)) grid.push_back(line);
            file.close();

            original_grid = grid;
            w = grid[0].size();
            h = grid.size();
            occupied = 0;
            changed_state = true;
            return true;
        }

        void reset() {
            grid = original_grid;
            occupied = 0;
            changed_state = true;
        }

        static char permute_seat1(int i, int j, vector<string> const& grid) {
            int w = grid[0].size();
            int h = grid.size();
            int occupied_near = 0;
            char current = grid[j][i];
            for (int dj = -1; dj <= 1; dj++) {
                for (int di = -1; di <= 1; di++) {
                    if (
                        (i + di >= 0) && (i + di < w) && 
                        (j + dj >= 0) && (j + dj < h) &&
                        ((dj != 0) || (di != 0))
                    ) {
                        if (grid[j + dj][i + di] == '#') occupied_near++;
                    }
                }
            }
            if ((current == 'L') && (occupied_near == 0)) return '#';
            if ((current == '#') && (occupied_near >= 4)) return 'L';
            return current;
        }

        static char permute_seat2(int i, int j, vector<string> const& grid) {
            int w = grid[0].size();
            int h = grid.size();
            int occupied_near = 0;
            char current = grid[j][i];
            char seat;
            int k;
            for (int dj = -1; dj <= 1; dj++) {
                for (int di = -1; di <= 1; di++) {
                    k = 1;
                    while (
                        (i + k * di >= 0) && (i + k * di < w) &&
                        (j + k * dj >= 0) && (j + k * dj < h) &&
                        ((dj != 0) || (di != 0))
                    ) {
                        seat = grid[j + k * dj][i + k * di];
                        if (seat == '#') {
                            occupied_near++;
                            break;
                        }
                        if (seat == 'L') break;
                        k++;
                    }
                }
            }
            if ((current == 'L') && (occupied_near == 0)) return '#';
            if ((current == '#') && (occupied_near >= 5)) return 'L';
            return current;
        }

        void iterate() {
            vector<string> new_grid (grid);
            char state;
            changed_state = false;
            occupied = 0;
            for (int j = 0; j < h; j++) {
                for (int i = 0; i < w; i++) {
                    state = permute_seat(i, j, grid);
                    new_grid[j][i] = state;
                    if (state == '#') occupied++;
                    if (state != grid[j][i]) changed_state = true;
                }
            }
            grid = new_grid;
        }

        void run1() {
            reset();
            permute_seat = permute_seat1;
            while (changed_state) iterate();
        }

        void run2() {
            reset();
            permute_seat = permute_seat2;
            while (changed_state) iterate();
        }

        void print() {
            for (string line: grid) {
                cout << line << endl;
            }
            cout << endl;
        }
};


int main() {
    SeatMap seat_map;
    seat_map.load_from_file("day11_input.txt");

    // Part 1
    seat_map.run1();
    cout << seat_map.occupied << endl;

    // Part 2
    seat_map.run2();
    cout << seat_map.occupied << endl;
}