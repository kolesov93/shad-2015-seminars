#include "testlib.h"
#include <vector>

using namespace std;

bool check(vector<int> a) {
    int n = a.size();
    vector<int> b(n);
    for (int i = 0; i < n; ++i) {
        if (a[i] > i) return false;
        if (a[i]) {
            b[i] = b[ a[i] - 1];
        } else {
            b[i] = i;
        }
    }

    for (int i = 1; i < n; ++i) {
        int k = a[i - 1];
        while (k && b[k] != b[i]) {
            k = a[k - 1];
        }
        if (b[k] == b[i]) ++k;
        if (k != a[i]) return false;
    }

    return true;
}

int main()
{
    registerValidation();

    int n = inf.readLong(1, 1000000, "n");
    vector<int> a(n);
    inf.readEoln();
    for (int i = 0; i < n; ++i) {
        a[i] = inf.readLong(0, 2000000000, format("pi[%d]", i));
        if (i + 1 != n) inf.readSpace();
    }
    inf.readEoln();
    inf.readEof();

    quitif(!check(a), _fail, "Given sequence is not correct failure table");


    return 0;
}

