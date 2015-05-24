#include "testlib.h"
#include <set>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <memory.h>

using namespace std;
const int N = 100000;
const int M = 1000000;
bool used[N];

int main() {
    registerValidation();

    int n = inf.readInt(1, N);
    inf.readEoln();

    int sumk = 0;
    for (int i = 1; i <= n; ++i) {
        int k = inf.readInt(1, M);
        sumk += k;
        quitif(sumk > M, _fail, "Number of wanted girls must not exceed %d", M);
        set<int> currentGirls;
        for (int j = 0; j < k; ++j) {
            inf.readSpace();
            int girl = inf.readInt(1, N, "number of girl");
            quitif(used[girl], _fail, "girl must be used exactly once (check it for girl #%d)", girl);
            quitif(currentGirls.find(girl) != currentGirls.end(), _fail, "girl %d is used twice for boy %d", girl, i);
            currentGirls.insert(girl);
        }
        inf.readEoln();
    }
    inf.readEof();

    return 0;
}

