/*
Problem: http://codeforces.com/problemset/problem/112/A
Date: 2017-12-01
*/
#include <iostream>
#include <string>
#include <vector>

#include "sort_algorithm.h"

using namespace std;

class CString
{
public:
  CString(const char* cs) : s_(cs)
  {
  }

  string& GetValueRef()
  {
    cout << "ref_address = " << &s_ << endl;
    return s_;
  }

  string GetValue()
  {
    cout << "value_address = " << &s_ << endl;
    return s_;
  }

private:
  string s_;
};
//
//int main()
//{
//  //string s1, s2;
//  //cin >> s1 >> s2;
//  //cout << s1.compare(s2);
//  //CString cstr("ref");
//  //string s = cstr.GetValueRef();
//
//  //cout << &cstr.GetValue() << " " << &cstr.GetValueRef() << " " << &s << endl;
//
//  //vector<int> v{3, 2, 4, 1};
//
//  //for (auto e : v)
//  //  cout << e << " ";
//  //cout << endl;
//  //
//  //BubbleSort(v.begin(), v.end());
//  ////int arr[] = { 85, 24, 63, 45, 17, 31, 96, 50 };
//  ////int len = (int) sizeof(arr) / sizeof(*arr);
//  ////quick_sort(arr, len);
//
//  //for (auto e : v)
//  //  cout << e << " ";
//  //cout << endl;
//
//
//  for (const char* key = ""; key != "i"; key = "k") {
//    key = "b";
//  }
//
//
//  return 0;
//}