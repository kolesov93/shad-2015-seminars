#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

vector<vector<int>> g;
vector<int> path;

void dfs(int x) {
    while (g[x].size()) {
        int y = g[x].back();
        g[x].pop_back();
        dfs(y);
    }
    path.push_back(x);
}

int main() {
    int n, k;
    cin >> n >> k;

    if (n == 1) {
        while (k--) {
            cout << 'a';
        }
        cout << endl;
        return 0;
    }
    if (k == 1) {
        for (int i = 0; i < n; ++i) cout << char('a' + i);
        cout << endl;
        return 0;
    }

    int all = 1;
    for (int i = 1; i < k; ++i) all *= n;

    g.resize(all);
    for (int i = 0; i < all; ++i) {
        for (int j = 0; j < n; ++j) {
            g[i].push_back((i * n + j) % all);
        }
    }
    dfs(0);

    string ans;
    for (int i = 1; i < k; ++i) ans += char('a');
    path.pop_back();
    for (auto it = path.rbegin(); it != path.rend(); ++it) {
        ans += char('a' + (*it % n));
    }
    cout << ans << endl;

    return 0;
}

