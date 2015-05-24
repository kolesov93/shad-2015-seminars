#include "testlib.h"
#include <vector>
#include <string>
#include <set>
#include <iostream>
#include <memory.h>

using namespace std;
const int V = 100000;
const int E = 250000;

set<pair<int, int>> q;

int main() {
    registerValidation();

    int n = inf.readInt(1, V, "n");
    inf.readSpace();
    int m = inf.readInt(0, E, "n");
    inf.readEoln();

    for (int e = 0; e < m; ++e) {
        int a = inf.readInt(1, n, format("a_%d", e + 1));
        inf.readSpace();
        int b = inf.readInt(1, n, format("b_%d", e + 1));
        pair<int,int> edge(a,b);
        quitif(q.find(edge) != q.end(), _fail, "edge (%d,%d) was used more than once", a, b);
        q.insert(edge);
        inf.readEoln();
    }
    inf.readEof();

    return 0;
}

