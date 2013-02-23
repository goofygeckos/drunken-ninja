#include <iostream>
#include <map>
#include <math.h>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

typedef long long int int64;

double distance(double x1, double y1, double x2, double y2) {
  double dx = x1 - x2;
  double dy = y1 - y2;
  return sqrt(dx * dx + dy * dy);
}

double average(const vector<double>& numbers, const vector<double>& weights) {
  double result = 0, weight_sum = 0;
  for (int i = 0; i < numbers.size(); ++i) {
    result += numbers[i] * weights[i];
    weight_sum += weights[i];
  }
  result /= weight_sum;
//   cout << "average: result = " << result << endl;
  return result;
}


int main(int argc, char** argv) {
  // Parsing.
  int n;
  scanf("%d", &n);
  vector<double> x(n), y(n);

  for (int i = 0; i < n; ++i) {
    scanf("%lf %lf", &x[i], &y[i]);
  }

//   cout << "n = " << n << endl;
  for (int i = 0; i < n; ++i) {
//     cout << x[i] << " " << y[i] << endl;
  }

  // Initialize the estimate to the centroid.
  double current_x = 0, current_y = 0;
  for (int i = 0; i < n; ++i) {
    current_x += x[i];
    current_y += y[i];
  }
  current_x /= n;
  current_y /= n;

  double delta = 10;
  int num_iterations = 0;
  while (delta > 0.0001 / 100000) { // 100 000 times the needed precision
    // Compute the weights.
    vector<double> weights(n);
    for (int i = 0; i < n; ++i) {
      weights[i] = 1.0 / distance(current_x, current_y, x[i], y[i]);
//       cout << "weights[" << i << "] = " << weights[i] << endl;
    }

    double new_x = average(x, weights);
    double new_y = average(y, weights);

    delta = fabs(new_x - current_x) + fabs(new_y - current_y);
//     cout << "delta = " << delta;
    if (++num_iterations % 1000 == 0) {
//       cout << num_iterations << " iterations: delta = " << delta << endl;
    }
    current_x = new_x;
    current_y = new_y;
  }

  cerr << num_iterations << " iterations" << endl;
  cout << current_x << " " << current_y << endl;
}
