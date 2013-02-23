#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  // Read in bytes
  vector<char> bytes;
  char c;
  while (scanf("%c", &c) == 1) {
    bytes.push_back(c);
  }
  
  reverse(bytes.begin(), bytes.end());

  int address = 0;

  bool first = true;
  for (int i = 0, pack = 0; i < bytes.size(); ++i) {
    pack = (pack << 8) | bytes[i];
    if ((i + 1) % 4 == 0 || i == bytes.size() - 1) {
      if (first) {
        first = false;
        cout << "PUSH 0" << endl; address++;
      } else {
        cout << "PUSH 1" << endl; address++;
      }
      cout << "PUSH " << pack << endl; address++;
    }
  }

  cout << "PUSH 256" << endl;
  cout << "DIV" << endl;
  cout << "OUT" << endl;
  cout << "PUSH 256" << endl;
  cout << "DIV" << endl;
  cout << "OUT" << endl;
  cout << "PUSH 256" << endl;
  cout << "DIV" << endl;
  cout << "OUT" << endl;

  cout << "OUT" << endl;
  cout << "PUSH -12" << endl;
  cout << "JGZ" << endl;

  return 0;
}
