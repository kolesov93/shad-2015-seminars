
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;
const int N = 100111;
const int K = 11;
int d[K][N];
vector<pair<int,int> > g[N];

struct cell {
    int vertex, level;
    int value;

    cell(int av = 0, int al = 0, int ap = 0)
        : vertex(av)
        , level(al)
        , value(ap)
    {}

    bool operator<(const cell& A) const {
        return value > A.value;
    }
};

int main() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    while (m--) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        --a; --b;
        g[a].emplace_back(b, c);
        g[b].emplace_back(a, c);
    }

    memset(d, 63, sizeof(d));
    d[0][0] = 0;
    priority_queue<cell> q;
    q.emplace(0, 0, 0);
    while (!q.empty()) {
        cell T = q.top(); q.pop();
        if (d[T.level][T.vertex] < T.value) continue;

        for (auto edge : g[T.vertex]) {
            int nd = T.value + edge.second;
            if (nd < d[T.level][edge.first]) {
                d[T.level][edge.first] = nd;
                q.emplace(edge.first, T.level, nd);
            }
            if (T.level + 1 <= k) {
                nd = T.value;
                if (nd < d[T.level + 1][edge.first]) {
                    d[T.level + 1][edge.first] = nd;
                    q.emplace(edge.first, T.level + 1, nd);
                }
            }
        }

        if (T.level + 1 <= k) {
            int nd = T.value;
            if (nd < d[T.level + 1][T.vertex]) {
                d[T.level + 1][T.vertex] = nd;
                q.emplace(T.vertex, T.level + 1, nd);
            }
        }
    }

    cout << d[k][n - 1] << endl;

    return 0;
}

