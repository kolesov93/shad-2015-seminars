#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;
const int N = 1111;
char w[N][N];

struct edge {
    edge(int a = 0, int b = 0, int c = 0)
        : end(a)
        , capacity(b)
        , back_edge(c)
    {}

    int end;
    int capacity;
    int back_edge;
};
vector<edge> g[N + N];

inline void add(int a, int b, int c) {
    g[a].emplace_back(b, c, g[b].size());
    g[b].emplace_back(a, 0, int(g[a].size()) - 1);
}

bool used[N + N];
int finished[N + N];
int S, T;
int IT;

int dfs(int x, int flow) {
    if (x == T) {
        return flow;
    }

    used[x] = true;
    int whole = 0;
    for (auto& edge : g[x]) {
        if (edge.capacity > 0 && !used[edge.end] && finished[edge.end] < IT) {
            int result = dfs(edge.end, min(edge.capacity, flow));
            if (result > 0) {
                edge.capacity -= result;
                flow -= result;
                g[edge.end][edge.back_edge].capacity += result;
                whole += result;
            }
            if (!flow) break;
        }
    }
    used[x] = false;
    if (whole == 0) {
        finished[x] = IT;
    }

    return whole;
}

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        cin >> w[i];
    }

    S = n + m + 1;
    T = S + 1;
    for (int i = 0; i < n; ++i) {
        int cnt = 0, cnt0 = 0, cnt1 = 0;
        for (int j = 0; j < m; ++j)
            if (w[i][j] == 'o') {
                ++cnt;
                ++cnt0;
            } else if (w[i][j] == 'x') {
                ++cnt;
                ++cnt1;
            } else if (w[i][j] == '?') {
                add(i, n + j, 1);
                ++cnt;
            }

        int need = cnt / 2;
        if ((cnt & 1) || cnt0 > need || cnt1 > need) {
            puts("Poor Tak");
            return 0;
        }

        add(S, i, need - cnt0);
    }
    for (int j = 0; j < m; ++j) {
        int cnt = 0, cnt0 = 0, cnt1 = 0;
        for (int i = 0; i < n; ++i)
            if (w[i][j] == 'o') {
                ++cnt;
                ++cnt0;
            } else if (w[i][j] == 'x') {
                ++cnt;
                ++cnt1;
            } else if (w[i][j] == '?') {
                ++cnt;
            }

        int need = cnt / 2;
        if ((cnt & 1) || cnt0 > need || cnt1 > need) {
            puts("Poor Tak");
            return 0;
        }

        add(n + j, T, need - cnt0);
    }

    for (IT = 1; dfs(S, 1e9); ++IT);

    for (auto&& edge : g[S])
        if (edge.capacity > 0) {
            puts("Poor Tak");
            return 0;
        }

    for (int i = 0; i < n; ++i)
        for (auto&& edge : g[i])
            if (edge.end >= n && edge.end < n + m && edge.capacity == 0) {
                w[i][edge.end - n] = 'o';
            }

    puts("Happy Tak");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            if (w[i][j] == '?') w[i][j] = 'x';
        puts(w[i]);
    }

    return 0;
}

