#include <iostream>
#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <cstring>

using namespace std;

vector<string> a, b;
vector<int> ans;

int main() {
    int n, m;
    cin >> n;
    a.resize(n);
    ans.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    cin >> m;
    for (int i = 0; i < m; ++i) {
        string s;
        cin >> s;

        for (int j = 0; j < n; ++j)
            if (s.find(a[j]) != s.npos) ++ans[j];
    }

    for (int i = 0; i < n; ++i) cout << ans[i] << '\n';


    return 0;
}

