#include "testlib.h"
#include <set>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <memory.h>

using namespace std;
const int N = 100000;
const int M = 500000;
const int LIM = 1000000;
const int C = 10000;

int w[N];

int fath(int x) {
    if (w[x] != x) w[x] = fath(w[x]);
    return w[x];
}


int main() {
    registerValidation();

    int n = inf.readInt(1, N, "n");
    inf.readSpace();
    int m = inf.readInt(1, M, "m");
    inf.readSpace();
    int k = inf.readInt(1, M, "k");
    inf.readEoln();

    quitif(double(m) * k > LIM, _fail, "m * k is too large");


    for (int i = 1; i <= n; ++i) w[i] = i;

    for (int i = 1; i <= m; ++i) {
        int a, b, c;
        a = inf.readInt(1, n, format("a_%d", i)); inf.readSpace();
        b = inf.readInt(1, n, format("b_%d", i)); inf.readSpace();
        c = inf.readInt(1, C, format("c_%d", i)); inf.readEoln();
        w[fath(a)] = fath(b);
    }
    inf.readEof();

    quitif(fath(1) != fath(n), _fail, "1 and n is not connected");

    return 0;
}

