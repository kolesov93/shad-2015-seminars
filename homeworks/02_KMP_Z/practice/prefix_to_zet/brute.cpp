#include <iostream>
#include <stdio.h>
#include <cstring>
#include <cstdlib>

using namespace std;
const int N = 1000111;
int a[N], n;
int z[N];

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];

    for (int i = 1; i < n; ++i) {
        int k = a[i];
        while (k) {
            z[i - k + 1] = max(z[i - k + 1], k);
            k = a[k - 1];
        }
    }
    for (int i = 0; i < n; ++i) cout << z[i] << " ";
    cout << endl;



    return 0;
}

