#include "testlib.h"
#include <vector>
#include <string>
#include <map>
#include <iostream>

using namespace std;

int main() {
    registerValidation();

    string s = inf.readToken("[a-z]{2,300000}");
    inf.readEoln();

    int n = s.size();
    vector<int> array(n);
    vector<bool> was(n);
    for (int i = 0; i < n; ++i) {
        array[i] = inf.readInt(0, n - 1, format("suffix_array[%d]", i));
        quitif(was[array[i]], _fail, "Number %d occures in suffix array more than once", array[i]);
        was[array[i]] = true;
        if (i + 1 < n) {
            inf.readSpace();
        }
    }
    inf.readEoln();

    for (int i = 0; i + 1 < n; ++i) {
        int pos1 = array[i], pos2 = array[i + 1];
        int maxpos = max(pos1, pos2);
        bool done = false;
        for (int j = 0; maxpos + j <= n; ++j)
            if (s[pos1 + j] != s[pos2 + j]) {
                quitif(s[pos1 + j] > s[pos2 + j], _fail, "Suffix array doesn't correspond to string. %d-suffix (position %d) is bigger than %d-suffix (position %d)", pos1, i, pos2, i + 1);
                done = true;
                break;
            }
        if (!done) {
            quitif(pos1 < pos2, _fail, "Suffix array doesn't correspond to string. %d-suffix is prefix of %d-prefix but goes after in array", pos2, pos1);
        }
    }

    inf.readEof();

    return 0;
}

