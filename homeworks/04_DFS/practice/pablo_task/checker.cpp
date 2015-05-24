#include "testlib.h"
#include <algorithm>
#include <string>
#include <set>
#include <vector>

using std::max;
using std::string;
using std::set;
using std::vector;

struct query {
    int l, r, d, u, c;
};

struct node {
    size_t l, r;
    int color;
};

void push(vector<node>& nodes, size_t x) {
    if (nodes[x].color == -1) return;
    if (nodes[x].l != nodes[x].r) {
        nodes[x + x].color = nodes[x].color;
        nodes[x + x + 1].color = nodes[x].color;
        nodes[x].color = -1;
    }
}

struct segment_tree {
    vector<node> nodes;
    size_t position;

    void build(size_t x, size_t l, size_t r) {
        if (x >= nodes.size()) {
            nodes.resize(x + 1);
        }
        nodes[x].l = l; nodes[x].r = r; nodes[x].color = 0;
        if (l != r) {
            build(x + x, l, (l + r) >> 1);
            build(x + x + 1, ((l + r) >> 1) + 1, r);
        }
    }

    int findcolor(size_t x, size_t pos) {
        if (nodes[x].l > pos) return -1;
        if (nodes[x].r < pos) return -1;
        if (nodes[x].l == pos && nodes[x].r == pos) return nodes[x].color;
        push(nodes, x);
        return max(findcolor(x + x, pos), findcolor(x + x + 1, pos));
    }

    void docolor(size_t x, size_t l, size_t r, int color) {
        if (nodes[x].l > r || nodes[x].r < l) return;
        if (l <= nodes[x].l && nodes[x].r <= r) {
            nodes[x].color = color;
            return;
        }
        push(nodes, x);
        docolor(x + x, l, r, color);
        docolor(x + x + 1, l, r, color);
    }
};

struct segment_tree_2d {
    vector<segment_tree> nodes;
    size_t n;

    segment_tree_2d(size_t n)
        : n(n)
    {
        nodes.resize(n + 1);
        for (size_t i = 1; i <= n; ++i) {
            nodes[i].build(1, 1, n);
        }
    }

    int findcolor(size_t x, size_t y) {
        return nodes[x].findcolor(1, y);
    }

    void docolor(size_t x1, size_t y1, size_t x2, size_t y2, int color) {
        for (size_t x = x1; x <= x2; ++x) {
            nodes[x].docolor(1, y1, y2, color);
        }
    }
};

int main(int argc, char * argv[]) {
    setName("Checks pablo-task solution");
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    vector<vector<int> > a(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            a[i][j] = inf.readInt();
        }
    }

    vector<query> queries(n);
    set<int> used_colors;
    segment_tree_2d tree(n);
    for (int i = 0; i < n; ++i) {
        queries[i].c = ouf.readInt();
        queries[i].l = ouf.readInt();
        queries[i].d = ouf.readInt();
        queries[i].r = ouf.readInt();
        queries[i].u = ouf.readInt();
        quitif(used_colors.find(queries[i].c) != used_colors.end(), _wa, "Each color should be used exactly once, but color %d used at least twice", queries[i].c);
        used_colors.insert(queries[i].c);

        quitif(!(1 <= queries[i].c && queries[i].c <= n), _wa, "Color must be in range [1..%d] but value %d was specified", n, queries[i].c);
        quitif(!(1 <= queries[i].l && queries[i].l <= n), _wa, "All coordinates must be in range [1..%d] but value %d was specified", n, queries[i].l);
        quitif(!(1 <= queries[i].r && queries[i].r <= n), _wa, "All coordinates must be in range [1..%d] but value %d was specified", n, queries[i].r);
        quitif(!(1 <= queries[i].d && queries[i].d <= n), _wa, "All coordinates must be in range [1..%d] but value %d was specified", n, queries[i].d);
        quitif(!(1 <= queries[i].u && queries[i].u <= n), _wa, "All coordinates must be in range [1..%d] but value %d was specified", n, queries[i].u);
        tree.docolor(queries[i].l, queries[i].d, queries[i].r, queries[i].u, queries[i].c);
    }

    for (int x = 1; x <= n; ++x)
        for (int y = 1; y <= n; ++y) {
            int expected = a[x - 1][y - 1];
            int got = tree.findcolor(x, y);
            quitif(expected != got, _wa, "Cell at (%d,%d) must have color %d, but have %d", x, y, expected, got);
        }

    quitf(_ok, "answer is good");
}

