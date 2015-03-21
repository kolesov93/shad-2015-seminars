#include <iostream>
#include <stdio.h>
#include <cstring>
#include <cstdlib>

using namespace std;
const int N = 33;
int a[N], n;
int b[N];

void check() {
    for (int i = 0; i < n; ++i) {
        int res = 0;
        for (int k = i; k > 0; --k) {
            bool good = true;
            for (int j = 0; j < k; ++j)
                if (b[j] != b[i - k + j + 1]) {
                    good = false;
                    break;
                }
            if (good) {
                res = k;
                break;
            }
        }
        if (res != a[i]) return;
    }
    for (int i = 0; i < n; ++i) cout << b[i] << " ";
    cout << endl;
    exit(0);
}

void rec(int l, int mx) {
    if (l == n) {
        check();
        return;
    }

    for (int i = 0; i <= mx + 1; ++i) {
        b[l] = i;
        rec(l + 1, max(i, mx));
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    rec(0, -1);
    puts("-1");

    return 0;
}

