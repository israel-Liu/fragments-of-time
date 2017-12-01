/*
Problem: http://codeforces.com/problemset/problem/96/A
Date: 2017-12-01
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
	std::string s;
	cin >> s;
	std::vector<int> v(100);
	int cnt = 0;
	for (int i = 0; i < s.size(); ++i) {
		if (s[i] == s[i + 1]) v[cnt] += 1;
		if (s[i] != s[i + 1]) cnt++;
	}

	int max_cnt = *std::max_element(v.begin(), v.end()) + 1;
	cout << (max_cnt >= 7 ? "YES" : "NO");

	return 0;
}