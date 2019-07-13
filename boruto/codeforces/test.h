#pragma once

#include "test_maximum_subarray.h"
#include "test_basic_data_structures.h"
#include "test_math.h"

void Test0()
{
  TestMaxSubSlow();
  TestMaxSubFaster();
  TestMaxSubFastest();
}

void Test1()
{
  TestStack();
  TestQueue();
  TestList();
}

void Test2()
{
  Testfactorial();
}