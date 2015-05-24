#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;
const int N = 2222;
int a[N][N];
vector<int> g[N];
int l[N], r[N], u[N], d[N];
int degree[N];
vector<pair<int,int>> poses[N];

int sum[N][N];

inline int prv(int x) {
    return x & (x - 1);
}
inline int nxt(int x) {
    return x + x - prv(x);
}

void update(int sx, int sy, int cval) {
    for (int x = sx; x < N; x = nxt(x))
        for (int y = sy; y < N; y = nxt(y)) {
            sum[x][y] += cval;
        }
}
inline int findsum(int sx, int sy) {
    int ans = 0;
    for (int x = sx; x; x = prv(x))
        for (int y = sy; y; y = prv(y)) {
            ans += sum[x][y];
        }
    return ans;
}
int findsum(int x1, int y1, int x2, int y2) {
    return findsum(x2, y2) - findsum(x1 - 1, y2) - findsum(x2, y1 - 1) + findsum(x1 - 1, y1 - 1);
}

int main() {
    memset(l, 63, sizeof(l));
    memset(d, 63, sizeof(d));
    memset(u, 63 + 125, sizeof(u));
    memset(r, 63 + 125, sizeof(r));

    int n;
    int cx, cy;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) {
            scanf("%d", &a[i][j]);
            int color = a[i][j];
            if (color) {
                cx = i;
                cy = j;
                poses[color].emplace_back(i, j);
            }

            l[color] = min(l[color], i);
            r[color] = max(r[color], i);
            u[color] = max(u[color], j);
            d[color] = min(d[color], j);
        }
    for (int i = 1; i <= n; ++i) {
        if (l[i] > r[i]) {
            printf("%d %d %d %d %d\n", i, cx, cy, cx, cy);
            continue;
        }
        g[0].push_back(i);
        degree[i]++;
    }

    for (int color = 1; color <= n; ++color) {
        for (auto pos : poses[color])
            update(pos.first, pos.second, 1);

        for (int ncolor = 1; ncolor <= n; ++ncolor)
            if (color != ncolor) {
                int nl = max(l[color], l[ncolor]);
                int nr = min(r[color], r[ncolor]);
                int nd = max(d[color], d[ncolor]);
                int nu = min(u[color], u[ncolor]);

                if (nl > nr || nd > nu) continue;
                if (findsum(nl, nd, nr, nu) > 0) {
                    g[ncolor].push_back(color);
                    degree[color]++;
                }
            }

        for (auto pos : poses[color])
            update(pos.first, pos.second, -1);
    }


    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int x = q.front(); q.pop();
        if (x) {
            printf("%d %d %d %d %d\n", x, l[x], d[x], r[x], u[x]);
        }
        for (int y : g[x]) {
            if (--degree[y] == 0) {
                q.push(y);
            }
        }
    }

    return 0;
}

