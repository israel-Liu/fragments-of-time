#include "iterator.h"
#include "iterator"

#include <iterator>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

void UsingIteratorAdapter()
{ 
  vector<string> coll;

  copy(istream_iterator<string>(cin), istream_iterator<string>(), back_inserter(coll));

  sort(coll.begin(), coll.end());

  unique_copy(coll.cbegin(), coll.cend(), ostream_iterator<string>(cout, " "));
}
