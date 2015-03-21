#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

const int N = 1000111;

int n;
int a[N], b[N], p[N];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", a + i);
        if (a[i] > i) {
            puts("-1");
            return 0;
        }
        if (!a[i]) {
            b[i] = i;
        } else {
            b[i] = b[ a[i] - 1 ];
        }
    }


    bool good = true;
    for (int i = 1; i < n; ++i) {
        int& k = p[i] = p[i - 1];
        while (k && b[k] != b[i]) {
            k = p[k - 1];
        }
        if (b[k] == b[i]) ++k;
        if (p[i] != a[i]) {
            good = false;
            break;
        }
    }

    if (!good) {
        puts("-1");
        return 0;
    }
    for (int i = 0; i < n; ++i) printf("%d ", b[i]);
    cout << endl;

    return 0;
}

