#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<string> program;
vector<int> stack;
int instruction;

inline void die(const string& msg) {
  cerr << instruction << ": " << program[instruction]
       << ": " << msg << endl;
  cerr << "Stack:" << endl;
  for (int i = stack.size() - 1; i >= 0; --i)
    cerr << stack[i] << endl;
  exit(1);
}

void splitstring(const string &s, char delim, vector<string> &elems) {
  stringstream ss(s);
  string item;
  while (getline(ss, item, delim)) {
    elems.push_back(item);
  }
}

inline int parsearg(const string& s) {
  vector<string> tokens;
  splitstring(s, ' ', tokens);
  if (tokens.size() != 2)
    die("Cannot parse argument from " + s);
  return atoi(tokens[1].c_str());
}

inline bool startswith(const string& s, const string& t) {
  return s.find(t) == 0;
}

int main() {
  string line;
  while (getline(cin, line)) {
    program.push_back(line);
  }

  instruction = 0;
  while (1) {
    if (instruction < 0 || instruction >= program.size()) {
      cerr << "Stopping: instruction address out of program." << endl;
      break;
    }

    // Read next instruction and advance
    string& command = program[instruction++];

    // PUSH
    if (startswith(command, "PUSH")) {
      int a = parsearg(command);
      stack.push_back(a);
    }
    // OUT
    else if (startswith(command, "OUT")) {
      if (stack.size() < 1) {
        die("OUT stack read out of bounds.");
      }
      int a = stack.back(); stack.pop_back();
      if (a < 0 || a > 127)
        die("OUT character is out of bounds.");
      cout << (char) a;
    }
    // READ
    else if (startswith(command, "READ")) {
      if (stack.size() < 1) {
        die("READ stack read out of bounds.");
      }
      int a = stack.back(); stack.pop_back();
      if (a < (int) -stack.size() || a >= (int) stack.size()) {
        die("READ index out of bounds");
      }
      if (a >= 0)
        stack.push_back(stack[a]);
      else
        stack.push_back(stack[stack.size() + a]);
    }
    // JGZ
    else if (startswith(command, "JGZ")) {
      if (stack.size() < 2) {
        die("JGZ stack read out of bounds.");
      }
      int a = stack.back(); stack.pop_back();
      int b = stack.back(); stack.pop_back();
      if (b > 0)
        instruction += a;
    }
    // ADD
    else if (startswith(command, "ADD")) {
      if (stack.size() < 2) {
        die("ADD stack read out of bounds.");
      }
      int a = stack.back(); stack.pop_back();
      int b = stack.back(); stack.pop_back();
      stack.push_back(a + b);
    }
    // MUL
    else if (startswith(command, "MUL")) {
      if (stack.size() < 2) {
        die("MUL stack read out of bounds.");
      }
      int a = stack.back(); stack.pop_back();
      int b = stack.back(); stack.pop_back();
      stack.push_back(a * b);
    }
    // DIV
    else if (startswith(command, "DIV")) {
      if (stack.size() < 2) {
        die("DIV stack read out of bounds.");
      }
      int a = stack.back(); stack.pop_back();
      int b = stack.back(); stack.pop_back();
      int q = b / a;
      int r = b % a;
      stack.push_back(q);
      stack.push_back(r);
    }
  }
  return 0;
}
