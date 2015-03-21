#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

const int N = 1000111;

int n;
int a[N], b[N], p[N], z[N];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", a + i);
        if (!a[i]) {
            b[i] = i;
        } else {
            b[i] = b[ a[i] - 1 ];
        }
    }

    int l = 0, r = 0;
    z[0] = 0;
    for (int i = 1; i < n; ++i) {
        if (i < r) {
            z[i] = min(r - i, z[i - l]);
        }
        while (i + z[i] < n && b[i + z[i]] == b[z[i]]) ++z[i];
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    for (int i = 0; i < n; ++i) printf("%d ", z[i]);
    cout << endl;

    return 0;
}

