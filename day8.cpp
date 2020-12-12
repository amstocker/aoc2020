#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <set>
using namespace std;

enum Operation {
    ACC, JMP, NOP
};

class Instruction {
    public:
        Operation op;
        int val;
};

class Program {
    public:
        int line;
        int acc;
        vector<Instruction> code;
        set<int> history;

        Program() { reset(); }

        void reset() {
            line = 0;
            acc = 0;
            history.clear();
        }

        bool interpret_file(string file_name) {
            reset();
            code.clear();
            
            ifstream file (file_name);
            if (!file.is_open()) return false;

            regex instruction_pattern ("(acc|jmp|nop)\\s+([\\+|-][0-9]+)");
            smatch matches;

            string line, op;
            Instruction inst;
            while (getline(file, line)) {
                if (!regex_match(line, matches, instruction_pattern)) return false;
                
                op = matches[1];
                if      (op == "acc") inst.op = ACC;
                else if (op == "jmp") inst.op = JMP;
                else if (op == "nop") inst.op = NOP;
                else return false;
                
                inst.val = stoi(matches[2]);
                
                code.push_back(inst);
            }
            file.close();
            
            return true;
        }

        bool execute() {
            Instruction inst;
            while (line < code.size()) {
                if (history.find(line) != history.end()) {
                    return false;
                }
                history.insert(line);
                
                inst = code[line];
                switch (inst.op) {
                    case JMP:
                        line += inst.val;
                        break;
                    case ACC:
                        acc += inst.val;
                    case NOP:
                        line++;
                }
            }
            return true;
        }
};


bool swap_op(Instruction& inst) {
    if      (inst.op == JMP) inst.op = NOP;
    else if (inst.op == NOP) inst.op = JMP;
    else return false;
    return true;
}

int main() {
    Program p;
    p.interpret_file("day8_input.txt");

    // Part 1
    p.execute();
    cout << p.acc << endl;

    // Part 2
    int i = 0;
    while (i < p.code.size()) {
        if (swap_op(p.code[i])) {
            if (p.execute()) {
                cout << p.acc << endl;
                break;
            }
            swap_op(p.code[i]);
            p.reset();
        }
        i++;
    }
}