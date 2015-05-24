#include <iostream>
#include <algorithm>
#include <vector>
#include <memory.h>

using namespace std;

const int N = 22;
vector<int> g[N];
bool used[N];

void dfs(int x) {
    used[x] = true;
    for (int y : g[x])
        if (!used[y]) {
            dfs(y);
        }
}

int main() {
    int n, m;
    cin >> n >> m;
    if (n > N) {
        cout << 0 << endl;
    }
    while (m--) {
        int a, b;
        cin >> a >> b;
        g[--a].push_back(--b);
    }

    int ans = n - 1;
    int lim = 1 << n;
    for (int msk = 0; msk < lim; ++msk) {
        int cnt = 0;
        for (int i = 0; i < n; ++i)
            if (msk & (1 << i)) {
                ++cnt;
            }
        if (cnt >= ans) continue;

        for (int i = 0; i < n; ++i)
            if (msk & (1 << i)) {
                g[0].push_back(i);
            }
        memset(used, 0, sizeof(used));

        dfs(0);
        bool cool = true;
        for (int i = 0; i < n; ++i)
            if (!used[i]) {
                cool = false;
                break;
            }

        if (cool) ans = cnt;
        while (cnt--) g[0].pop_back();
    }

    cout << ans << endl;

    return 0;
}

