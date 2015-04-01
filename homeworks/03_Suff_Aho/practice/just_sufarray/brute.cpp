#include <iostream>
#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <set>

using namespace std;

int lcp(const string& a, const string& b) {
    int lim = min(a.size(), b.size());
    for (int i = 0; i < lim; ++i)
        if (a[i] != b[i]) return i;
    return lim;
}

int main() {
    string s;
    cin >> s;

    int n = s.size();
    set<string> q;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; i + j <= n; ++j) {
            q.insert(s.substr(i, j));
        }
    }

    int mx = 0;
    set<int> qq;
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j) {
            int val = lcp(s.substr(i), s.substr(j));
            mx = max(mx, val);
            qq.insert(val);
        }
    cout << q.size() << " " << mx << " " << qq.size() << endl;

    return 0;
}

