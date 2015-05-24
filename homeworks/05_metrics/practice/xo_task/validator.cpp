#include "testlib.h"
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <memory.h>

using namespace std;
const int N = 200;

int main() {
    registerValidation();

    int n = inf.readInt(1, N);
    inf.readSpace();
    int m = inf.readInt(1, N);
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        string line = inf.readString();
        quitif(int(line.size()) != m, _fail, "Row size must be %d, but %dth row have size %d", m, i + 1, int(line.size()));
        for (int j = 0; j < m; ++j) {
            char c = line[j];
            quitif(c != 'x' && c != 'o' && c != '?' && c != '*', _fail, "Only 'xo?*' are allowed, but found '%c' in (%d,%d)", c, i + 1, j + 1);
        }
    }
    inf.readEof();

    return 0;
}

