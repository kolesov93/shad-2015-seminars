#include "testlib.h"

using namespace std;

int main()
{
    registerValidation();

    int n = inf.readLong(1, 1000000, "n");
    inf.readEoln();
    for (int i = 0; i < n; ++i) {
        inf.readLong(0, 2000000000, format("pi[%d]", i));
        if (i + 1 != n) inf.readSpace();
    }
    inf.readEoln();
    inf.readEof();

    return 0;
}

