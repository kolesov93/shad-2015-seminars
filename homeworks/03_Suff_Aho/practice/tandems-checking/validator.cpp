#include "testlib.h"
#include <vector>
#include <string>
#include <map>
#include <iostream>

using namespace std;

int main() {
    registerValidation();

    string s = inf.readToken("[a-z]{2,300000}");
    int n = s.size();
    inf.readEoln();
    int q = inf.readInt(0, 100000);
    inf.readEoln();
    for (int i = 1; i <= q; ++i) {
        int l, k;
        l = inf.readInt();
        inf.readSpace();
        k = inf.readInt();
        inf.readEoln();

        quitif(l < 0 || l >= n, _fail, "l in %dth query equals to %d which exceeds bounds [0;%d)", i, l, n);
        quitif(k < 0 || k > n, _fail, "k in %dth query equals to %d which exceeds bounds [0;%d]", i, k, n);
    }
    inf.readEof();

    return 0;
}

