#include "testlib.h"
#include <vector>
#include <string>
#include <map>
#include <iostream>

using namespace std;

vector<map<char,int> > tree(1);

bool add(const string& s) {
    size_t cur = 0;
    bool cool = false;
    for (size_t i = 0; i < s.size(); ++i) {
        char c = s[i];
        if (tree[cur].find(c) == tree[cur].end()) {
            cool = true;
            tree[cur][c] = tree.size();
            tree.push_back(map<char,int>());
        }
        cur = tree[cur][c];
    }
    return cool;
}

int main() {
    registerValidation();
    const int N = 1000000;
    const int M = 1000000;
    const int NUM = 1000;

    int n = inf.readLong(1, NUM, "n");
    vector<string> a(n);
    inf.readEoln();
    size_t commonSize = 0;
    for (int i = 0; i < n; ++i) {
        a[i] = inf.readToken("[a-z]{1,1000000}");
        quitif(!add(a[i]), _fail, "Patterns don't form non-prefix code");
        inf.readEoln();
        commonSize += a[i].size();
    }
    quitif(commonSize > N, _fail, "Common size of patterns is too big (> %d)", N);

    int m = inf.readLong(1, NUM, "m");
    commonSize = 0;
    inf.readEoln();
    for (int i = 0; i < m; ++i) {
        const string& s = inf.readToken("[a-z]{1,1000000}");
        commonSize += s.size();
        inf.readEoln();
    }
    inf.readEof();
    quitif(commonSize > M, _fail, "Common size of texts is too big (> %d)", M);

    return 0;
}

