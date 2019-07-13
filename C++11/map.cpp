#include <algorithm>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <cctype>

using namespace std;

class RuntimeStringCmp
{
public:
  enum cmp_mode {normal, nocase};

public:
  RuntimeStringCmp(cmp_mode m = normal) : mode_(m)
  {
  }

  bool operator()(const string& s1, const string& s2) const
  {
    if (mode_ == normal) return s1 < s2;
    else return lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end(), nocase_compare);
  }

private:
  static bool nocase_compare(char c1, char c2)
  {
    return toupper(c1) < toupper(c2);
  }

private:
  const cmp_mode mode_;
};

using StringStringMap = map<string, string, RuntimeStringCmp>;

void FillAndPrint(StringStringMap& ssmap)
{
  // Insert elements in random order
  ssmap["Deutschland"] = "Germany";
  ssmap["deutsch"] = "German";
  ssmap["Haken"] = "snag";
  ssmap["arbeiten"] = "work";
  ssmap["Hund"] = "dog";
  ssmap["gehen"] = "go";
  ssmap["Unternehmen"] = "enterprise";
  ssmap["unternehmen"] = "undertake";
  ssmap["gehen"] = "walk";
  ssmap["Bestatter"] = "undertaker";

  // Print elements
  cout.setf(ios::left, ios::adjustfield);
  for (const auto& elem : ssmap) {
    cout << setw(15) << elem.first << " " << elem.second << endl;
  }
  cout << endl;
}

void UsingPowerMap()
{
  StringStringMap ssmap;
  FillAndPrint(ssmap);
  RuntimeStringCmp ignore_case(RuntimeStringCmp::nocase);
  StringStringMap ssmap_nocase(ignore_case);
  FillAndPrint(ssmap_nocase);
}