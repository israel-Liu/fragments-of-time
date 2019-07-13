#pragma once

#include <vector>
#include <iostream>

#include "maximum_subarray.h"

void TestMaxSubSlow()
{
  using std::vector;
  using std::cout;
  using std::endl;

  vector<int> v{ -2, -4, 3, -1, 5, 6, -7, -2, 4, -3, 2 };
  cout << MaxSubSlow(v) << endl;
  //cout << MaxSubFaster(v) << endl;
}

void TestMaxSubFaster()
{
  using std::vector;
  using std::cout;
  using std::endl;

  vector<int> v{ -2, -4, 3, -1, 5, 6, -7, -2, 4, -3, 2 };
  cout << MaxSubFaster(v) << endl;
}

void TestMaxSubFastest()
{
  using std::vector;
  using std::cout;
  using std::endl;

  vector<int> v{ -2, -4, 3, -1, 5, 6, -7, -2, 4, -3, 2 };
  cout << MaxSubFastest(v) << endl;
}