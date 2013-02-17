#include <stdio.h>
#include <vector>
#include <map>
#include <set>

using namespace std;

struct Painting {
  int index;
  double start;
  double value;
  vector<pair<int, double> > relations;
  int incoming;
};

int main(int argc, char** argv) {
  int size_p, size_r;
  scanf("%d %d", &size_p, &size_r);

  vector<Painting> ps(size_p);
  for (int i = 0; i < size_p; ++i) {
    scanf("%lf", &ps[i].start);
    ps[i].value = ps[i].start;
    ps[i].index = i;
    ps[i].incoming = 0;
  }

  for (int i = 0; i < size_r; ++i) {
    int a, b;
    double r;
    scanf("%d %d %lf", &a, &b, &r);
    ps[b - 1].relations.push_back(make_pair(a - 1, r));
    ps[a - 1].incoming++;
  }

  ////////////////////////////////////////
  // Topological sort

  // empty nodes
  set<int> empty;
  for (const auto& p : ps) {
    if (p.incoming == 0) empty.insert(p.index);
  }
  
  while (!empty.empty()) {
    int i = *empty.begin();
    empty.erase(empty.begin());
    const auto& p = ps[i];
    for (const auto& j_r : p.relations) {
      auto& pj = ps[j_r.first];
      pj.value += p.value * j_r.second;
      if (--pj.incoming == 0) empty.insert(pj.index);
    }
  }

  // Print output
  for (const auto& p : ps) {
    printf("%.3f ", p.value);
  }
}
