#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;
const int N = 200222;
vector<int> g[N], gt[N];
bool used[N];
int mark[N];
int inverse[N];
vector<int> order;

void dfs(int x) {
    used[x] = true;
    for (int y : g[x])
        if (!used[y]) dfs(y);
    order.push_back(x);
}

void dfs2(int x, int color) {
    mark[x] = color;
    for (int y : gt[x])
        if (!mark[y]) {
            dfs2(y, color);
        }
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        int k;
        scanf("%d", &k);
        for (int j = 0; j < k; ++j) {
            int x; scanf("%d", &x);
            if (j == 0) {
                g[n + x - 1].push_back(i);
                gt[i].push_back(n + x - 1);
                inverse[n + x - 1] = i;
            } else {
                g[i].push_back(n + x - 1);
                gt[n + x - 1].push_back(i);
            }
        }
    }

    /*
    for (int i = 0; i < n + n; ++i)
        for (int x : g[i]) cerr << i << " --> " << x << endl;
        */

    for (int i = 0; i < n + n; ++i)
        if (!used[i]) dfs(i);
    reverse(begin(order), end(order));

    int cur = 0;
    for (int x : order)
        if (!mark[x]) {
            dfs2(x, ++cur);
        }
    /*
    for (int x : order) cerr << x << ' ';
    cerr << endl;
    for (int i = 0; i < n + n; ++i) cerr << i << ": " << mark[i] << endl;
    */

    for (int i = 0; i < n; ++i) {
        vector<int> ans;
        for (int y : g[i])
            if (mark[i] == mark[ inverse[y] ]) {
                ans.push_back(y - n + 1);
            }
        sort(begin(ans), end(ans));
        printf("%d", int(ans.size()));
        for (int x : ans) printf(" %d", x);
        puts("");
    }

    return 0;
}

