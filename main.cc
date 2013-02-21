#include <iostream>
#include <map>
#include <set>
#include <stdio.h>
#include <vector>

using namespace std;

set<int> frequencies;

void RegisterBeep(int num_zeros, int num_samples) {
  if (num_samples < 2) {
    return;
  }
  // cout << "Register beep: " << num_zeros << ", " << num_samples << endl;
  double time_sec = num_samples / 44100.0;
  double freq = num_zeros / time_sec;

  int freq_int = static_cast<int>(freq / 100) * 100;
  frequencies.insert(num_zeros);
}

int main(int argc, char** argv) {
  unsigned char c;
  for (int i = 0; i < 44; ++i) {
    cin >> c;
  }

  unsigned char prev = 128;

  int num_zeros = 0;
  int num_samples = 0;
  while (cin >> c) {
    if (prev == c && prev == 128) {
      if (num_samples != 0) {
        RegisterBeep(num_zeros, num_samples);
      }
      num_zeros = 0;
      num_samples = 0;
      continue;
    }
    ++num_samples;
    if (prev < 128 && c >= 128) {
      ++num_zeros;
    }
    prev = c;
  }

  if (num_samples != 0) {
    RegisterBeep(num_zeros, num_samples);
  }

  cout << frequencies.size() << endl << endl;
  // for (set<int>::const_iterator it = frequencies.begin();
      // it != frequencies.end();
      // ++it) {
    // cout << *it << endl;
  // }
}
