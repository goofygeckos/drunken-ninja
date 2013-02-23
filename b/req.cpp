#include <stdio.h>
#include <vector>
#include <map>
#include <set>

using namespace std;

typedef long long int int64;

int main(int argc, char** argv) {
  int n, t;
  scanf("%d %d", &n, &t);

  // printf("%d n %d t\n", n, t);
  
  vector<int64> reqs(1 << n);
  for (int i = 0; i < reqs.size(); ++i)
    scanf("%lld", &reqs[i]);

  //  for (int64 r : reqs) printf("%lld ", r);

  for (int i = 0; i < t; ++i) {
    vector<int64> tmp(reqs.size());
    for (int64 j = 0; j < reqs.size(); ++j) {
      for (int64 k = j + 1; k < reqs.size(); ++k) {
	int64 p = j | k;
	// *2 to account for both directions
	tmp[p] += 2 * reqs[j] * reqs[k];
	if (tmp[p] >= 1000000007) 
	  tmp[p] = tmp[p] % 1000000007;
      }
    }
    for (int j = 0; j < reqs.size(); ++j) {
      reqs[j] += tmp[j];
      if (reqs[j] >= 1000000007) 
	reqs[j] = reqs[j] % 1000000007;
    }
  }

  // Print output
  printf("%lld\n", reqs[reqs.size() - 1]);
}
