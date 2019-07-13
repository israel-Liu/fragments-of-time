#pragma once

#include <vector>
#include <algorithm>

using std::vector;

int MaxSubSlow(const vector<int>& v)
{
  int sum = 0, n = v.size();
  for (int i = 0; i < n; ++i) {
    for (int j = i; j < n; ++j) {
      int s = 0;
      for (int k = i; k < j; ++k) {
        s += v[k];
      }
      if (s > sum) {
        sum = s;
      }
    }
  }

  return sum;
}

int MaxSubFaster(const vector<int>& v)
{
  int n = v.size();
  vector<int> s(n);
  s[0] = v[0];

  for (int i = 1; i < n; ++i) {
    s[i] = s[i - 1] + v[i];
  }

  int max_sum = 0;

  for (int i = 1; i < n; ++i) {
    int sub_sum = 0;
    for (int j = i; j < n; ++j) {
      sub_sum = s[j] - s[i - 1];
      if (sub_sum > max_sum) max_sum = sub_sum;
    }
  }

  return max_sum;
}

int MaxSubFastest(const vector<int>& v)
{
  int n = v.size();
  vector<int> m(n);
  m[0] = v[0];

  for (int i = 1; i < n; ++i)
    m[i] = std::max(0, m[i - 1] + v[i]);

  int max_sum = 0;

  for (int i = 1; i < n; ++i)
    max_sum = std::max(max_sum, m[i]);

  return max_sum;
}