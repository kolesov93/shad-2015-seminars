#include "testlib.h"
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <memory.h>

using namespace std;
const int MAGIC = 1000;

vector<int> g[MAGIC];
int u[MAGIC], d[MAGIC], l[MAGIC], r[MAGIC];
int a[MAGIC][MAGIC];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
int mark[MAGIC];
bool cycled;

void dfs(int x) {
    mark[x] = 1;
    for (int y : g[x]) {
        if (mark[y] == 1) {
            cycled = true;
            return;
        }
        if (mark[y] == 0) {
            dfs(y);
        }
    }
    mark[x] = 2;
}

int main() {
    registerValidation();

    memset(l, 63, sizeof(l));
    memset(d, 63, sizeof(d));
    memset(u, 63 + 125, sizeof(u));
    memset(r, 63 + 125, sizeof(r));

    int n = inf.readInt(1, MAGIC);
    l[0] = 0; r[0] = n - 1;
    d[0] = 0; u[0] = n - 1;

    inf.readEoln();
    bool was = false;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int color = a[i][j] = inf.readInt(0, n, format("color[%d,%d]", i + 1, j + 1));
            if (a[i][j]) {
                was = true;
                l[color] = min(l[color], i);
                r[color] = max(r[color], i);
                u[color] = max(u[color], j);
                d[color] = min(d[color], j);
            }
            if (j + 1 < n) inf.readSpace();
        }
        inf.readEoln();
    }
    inf.readEof();
    quitif(!was, _fail, "There is no colored cell");

    for (int i = 1; i <= n; ++i) {
        g[0].push_back(i);
    }

    for (int x = 0; x < n; ++x)
        for (int y = 0; y < n; ++y) {
            int color = a[x][y];
            if (!color) continue;

            for (int c = 0; c < 4; ++c) {
                int nx = x + dx[c];
                int ny = y + dy[c];

                if (0 <= nx && nx < n && 0 <= ny && ny < n) {
                    int ncolor = a[nx][ny];
                    if (ncolor != color) {
                        if (l[color] <= nx && nx <= r[color] && d[color] <= ny && ny <= u[color]) {
                            g[color].push_back(ncolor);
                        }
                    }
                }
            }
        }

    dfs(0);
    quitif(cycled, _fail, "Found cycle in color dependicies");

    return 0;
}

