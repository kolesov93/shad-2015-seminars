#include "testlib.h"
#include <vector>
#include <string>
#include <map>
#include <iostream>

using namespace std;
const int MAGIC = 3000000;

int main() {
    registerValidation();

    int n = inf.readInt(1, 26);
    inf.readSpace();
    int k = inf.readInt(1, 100);
    inf.readEoln();

    typedef long long ll;
    ll whole = 1;
    for (int i = 0; i < k; ++i) {
        whole *= n;
        quitif(whole > MAGIC, _fail, "n^p is too big (> %d)", MAGIC);
    }

    inf.readEof();

    return 0;
}

