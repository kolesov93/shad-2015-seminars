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

bool used[N + N], finished[N + N];
int S, T;

int dfs(int x, int flow) {
    if (x == T) {
        return flow;
    }

    used[x] = true;
    int whole = 0;
    for (auto& edge : g[x]) {
        if (edge.capacity > 0 && !finished[edge.end] && !used[edge.end]) {
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
        finished[x] = true;
    }

    return whole;
}

int main() {
    srand(time(0));
    int n, m;
    cin >> n >> m;
    if ((n & 1) != (m & 1)) ++n;
    bool swapped = false;
    if (n < m) {
        swap(n, m);
        swapped = true;
    }

    S = n + m + 1;
    T = S + 1;
    vector<pair<int,int>> edges;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            edges.emplace_back(i, n + j);
    random_shuffle(begin(edges), end(edges));
    for (auto&& edge : edges)
        add(edge.first, edge.second, 1);

    int whole = 0;
    for (int i = 0; i < n; ++i) {
        int howmuch = rand() & 1 ? 0 : 2;
        if (m & 1) {
            ++howmuch;
        }
        add(S, i, howmuch);
        whole += howmuch;
    }
    vector<int> caps(m, n & 1);
    int csum = m * (n & 1);
    while (csum < whole) {
        caps[rand() % caps.size()] += 2;
        csum += 2;
    }
    for (int i = 0; i < m; ++i)
        add(n + i, T, caps[i]);

    while (dfs(S, 1e9)) {
        memset(finished, 0, sizeof(finished));
    }

    memset(w, '?', sizeof(w));
    for (int i = 0; i < n; ++i)
        for (auto&& edge : g[i])
            if (edge.end >= n && edge.end < n + m && edge.capacity == 0) {
                if (swapped) {
                    w[i][edge.end - n] = '*';
                } else {
                    w[edge.end - n][i] = '*';
                }
            }

    if (swapped) swap(n, m);
    cout << n << " " << m << endl;
    for (int i = 0; i < n; ++i) {
        w[i][m] = 0;
        puts(w[i]);
    }

    return 0;
}

