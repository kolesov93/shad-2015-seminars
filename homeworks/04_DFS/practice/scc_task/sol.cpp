#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;
const int N = 100111;
vector<int> g[N], g2[N];
vector<int> order;
int mark[N];
bool used[N];
int degree[N];

void dfs(int x) {
    used[x] = true;
    for (int y : g[x])
        if (!used[y]) {
            dfs(y);
        }
    order.push_back(x);
}

void dfs2(int x, int num) {
    if (mark[x]) {
        return;
    }
    mark[x] = num;
    for (int y : g2[x]) {
        dfs2(y, num);
    }
}

int main() {
    int n, m;
    scanf("%d%d",&n,&m);

    while (m--) {
        int a, b;
        scanf("%d%d",&a,&b);
        g[a].push_back(b);
        g2[b].push_back(a);
    }

    for (int v = 1; v <= n; ++v) {
        if (!used[v]) dfs(v);
    }
    reverse(begin(order), end(order));
    int cnum = 0;
    for (int x : order) {
        if (!mark[x]) {
            dfs2(x, ++cnum);
        }
    }
    for (int v = 1; v <= n; ++v)
        for (int x : g[v])
            if (mark[v] != mark[x]) {
                ++degree[mark[x]];
            }
    int ans = 0;
    for (int i = 1; i <= cnum; ++i)
        if (!degree[i]) {
            ++ans;
        }
    if (!degree[mark[1]]) --ans;

    cout << ans << endl;

    return 0;
}

